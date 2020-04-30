from typing import List, Text
from . import utils
from . import model
from .parser import Parser
from .loader import ModelLoader, Transformer, TransformerPass

class _LazyModelObject(object):
    def __init__(self, loader: ModelLoader, refid: Text):
        self._loader = loader
        self._refid = refid
        self._model = None

    @property
    def __model__(self):
        if not self._model:
            self._model = self._loader.load(self._refid)
            try:
                self._on_content_loaded(self._model)
            except AttributeError:
                pass
        return self._model


class _LazyModelProperty(object):
    def __init__(self, wrapped_descriptor):
        self._desc = wrapped_descriptor

    def __get__(self, instance, owner):
        return self._desc.__get__(instance.__model__, owner)

    def __set__(self, instance, value):
        return self._desc.__set__(instance.__model__, value)


def _lazy_model(model_cls):
    def wrapper(user_cls):
        class Lazy(_LazyModelObject, model_cls, user_cls):
            def __init__(self, loader: ModelLoader, refid: Text,
                               *args, **kwargs):
                _LazyModelObject.__init__(self, loader, refid)
                user_cls.__init__(self, *args, **kwargs)
                model_cls.__init__(self)

        for field in model_cls.__fields__:
            desc = getattr(Lazy, field)
            setattr(Lazy, field, _LazyModelProperty(desc))

        return Lazy
    return wrapper


@_lazy_model(model.Class)
class LazyClass(object):
    pass

@_lazy_model(model.Namespace)
class LazyNamespace(object):
    pass

class Index(object):
    def __init__(self, parser: Parser, loader: ModelLoader):
        assert parser
        assert loader
        self._parser = parser
        self._loader = loader
        self._index = self._initialize()

    def find(self, query: str):
        try:
            model = self._index[query].__model__
        except KeyError:
            try:
                model = self._find_inner(query)
            except KeyError:
                raise KeyError(f'Cannot find "{query}"')
        return model

    @utils.return_dict
    def _initialize(self):
        index = self._parser.parse('index')
        allowed_kinds = {'class', 'strcut', 'namespace'}
        for entry in index.compound:
            if entry.kind in allowed_kinds:
                model_object = _LazyModelObject(self._loader, entry.refid)
                yield entry.name, model_object

    def _find_inner(self, query):
        parent_name, name = utils.split_compound_name(query)
        model = self._index[parent_name].__model__
        if hasattr(model, 'functions'):
            for func in model.functions:
                if func.name == name:
                    return func
        raise KeyError(f'Cannot find {name} inside {parent_name}')


def index(doxygen_xml_dir: Text,
          transformer_passes: List[TransformerPass] = []) -> Index:
    parser = Parser(doxygen_xml_dir)
    transformer = Transformer(transformer_passes)
    loader = ModelLoader(parser, transformer)
    return Index(parser, loader)

def to_dict(index: Index, discard_empty=False):
    index_dict = _to_dict(index)
    if discard_empty:
        index_dict = _discard_empty(index_dict)
    return index_dict

def to_json(index: Index, discard_empty=False, **kwargs):
    import json
    return json.dumps(to_dict(index, discard_empty), **kwargs)

def to_yaml(index: Index, discard_empty=False, **kwargs):
    import yaml
    return yaml.dump(to_dict(index, discard_empty), **kwargs)

@utils.return_dict
def _to_dict(index: Index):
    for k, v in index._index.items():
        yield k, _index_to_dict(v.__model__)

def _discard_empty(obj):
    if isinstance(obj, list):
        gen = (_discard_empty(x) for x in obj)
        obj = [x for x in gen if x]
    elif isinstance(obj, dict):
        gen = ((k, _discard_empty(x)) for k, x in obj.items())
        obj = {k: x for k, x in gen if x}
    if obj:
        return obj

def _index_to_dict(obj, discard_empty=False):
    if isinstance(obj, list):
        return [_index_to_dict(x) for x in obj]
    elif isinstance(obj, dict):
        return {k: _index_to_dict(x) for k, x in obj.items()}
    elif model.has_fields(obj):
        obj_dict = {}
        for field in obj.iter():
            value = getattr(obj, field)
            obj_dict[field] = _index_to_dict(value)
        return obj_dict
    return obj
