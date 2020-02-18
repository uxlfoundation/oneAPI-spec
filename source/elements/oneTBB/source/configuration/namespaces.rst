==========
Namespaces
==========

This section describes the oneAPI Threading Building Blocks namespace conventions.


tbb Namespace
-------------

Namespace 
``tbb`` contains public identifiers defined by the library
that you can reference in your program.

tbb::flow Namespace
-------------------

Namespace 
``tbb::flow`` contains public identifiers defined by the
library that you can reference in your program related to the flow graph feature. See 
:doc:`Flow Graph <../flow_graph>` for more information .

tbb::interfacex Namespace
-------------------------

Namespaces of the form 
``tbb::interfacex`` define public identifiers that
the library injects into namespace 
``tbb``. The numeral 
``x`` corresponds to an internal version number
that serves to prevent accidental linkage of incompatible definitions. Your
code should never directly reference namespaces prefixed with 
``tbb::interfacex``. Instead, reference names via
namespace 
``tbb``.

For example the header 
``tbb/concurrent_hash_map.h`` defines the template 
``concurrent_hashmap<Key,T>`` as 
``tbb::version4::concurrent_hashmap<Key,T>`` and
employs a 
``using`` directive to inject it into namespace 
``tbb``. Your source code should reference it as 
``tbb::concurrent_hashmap<Key,T>``.

tbb::internal Namespace
-----------------------

Namespace 
``tbb::internal`` serves a role similar to 
``tbb::interfacex``. It is retained for backwards
compatibility with older versions of the library. Your code should never
directly reference namespace 
``tbb::internal``. Indirect reference via a public 
``typedef`` provided by the header files is permitted.

tbb::deprecated Namespace
-------------------------

The library uses the namespace 
``tbb::deprecated`` for deprecated identifiers that have
different default meanings in namespace 
``tbb``. Compiling with 
``TBB_DEPRECATED=1`` causes such identifiers to replace
their counterpart in namespace tbb.

tbb::strict_ppl Namespace
-------------------------

The library uses the namespace 
``tbb::strict_ppl`` for identifiers that are put in
namespace 
``Concurrency`` when ``tbb/compat/ppl.h`` is
included.