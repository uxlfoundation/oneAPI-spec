__version__ = '0.0.1'

def setup(app):
    from . import directives
    directives.setup(app)
    return {
        'version': __version__,
        'parallel_read_safe': True,
        'parallel_write_safe': True
    }
