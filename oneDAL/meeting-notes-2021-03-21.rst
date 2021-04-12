************************
Meeting notes 2021-03-31
************************

Agenda
------

- Org changes in the team
- Deprecation of some methods of ``dal::array`` class.

Org changes in the team
-----------------------

Decision: extend the team with additional members for a better support and
development of the specs.

API deprecation
---------------

**Array class specification**: https://spec.oneapi.com/versions/latest/elements/oneDAL/source/data_management/array.html

**Deprecation proposal**: `oneDAL/proposals/2021-03-21/array-methods-deprecation.rst`


1. Approve proposed changes

2. Review interfaces of array class to clarify whether similar modifications are
   required in other methods, e.g., ``reset()``

3. Modify the example or provide additional examples reflecting the
   proposed changes

4. Review and clean-up description of the methods of the ``dal::array``
   reflecting the proposed changes

5. Synchronize implementation including documentation and the specs. This work
   can be done iteratively on regular basis by including particular tasks
   in the sprints of the developer team.
