---------------------
oneVPL API Versioning
---------------------

oneVPL is the successor to |msdk_full_name|. oneVPL API versioning starts from
2.0. There is a correspondent version of |msdk_full_name| API which is used as a basis
for oneVPL and defined as ``MFX_LEGACY_VERSION`` macro.

Experimental APIs in oneVPL are protected with the following macro::

   #if (MFX_VERSION >= MFX_VERSION_NEXT)

To use the API, define the ``MFX_VERSION_USE_LATEST`` macro.