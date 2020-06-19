============
 Versioning
============

Decisions to be made:

Components
==========

Versioning scheme?

  semantic versioning

Link product versioning and spec versioning?

  No.

  Products are supersets of individual specs. They contain extensions
  or may contain components unrelated by the spec. Product versions
  must take into account all components, not just a single spec We can
  begin with the same version numbering, but they may diverge in the
  future.

Initial major version is 1 or year?

  1.

  It is customary and preferred. Year would be valuable if product
  2025 always implemented spec 2025. Since we cannot guarantee the
  relations, no benefit to use year.

Whole spec
===========

Versioning scheme?

  semantic versioning. If any component bumps major version, then
  whole spec bumps major version. Same for minor version.

  Calendar is appropriate if there is no way to follow semantic
  version rules and provide useful info. An example would be a large
  collection of software where it isn't possible to coordinate betwen
  the components. End users and software distribuors (toolkits) must
  monitor versions of individual compnents to ensure upgrades will not
  break code.

  Whole spec semantic simplies talking about and assembling
  collections of software, at the expense of freedom of the invidiual
  components. To be useful, it requires some discipline when
  individual components can bump major versions, so it happens on a
  manageable cadence.

Link product versioning and spec versioning?

  No

  Product versioning is driven by marketing, not pure semantic versioning.

Initial major version is 1 or year?

  1.

  Same reasoning as component.
  
  



  
