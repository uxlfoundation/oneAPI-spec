.. SPDX-FileCopyrightText: 2020-2021 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. _graph-section:

===============
Graph extension
===============

oneDNN Graph extension is a flexible graph interface to maximize
operation fusions in a scalable way. oneDNN Graph API accepts a full
computational graph as input and performs a engine-aware graph
partitioning, where sub-graphs of operations that are candidate for
fusion are grouped together. Those partitions are then compiled and
executed as fused operations.

.. toctree::
   :maxdepth: 1

   general.rst
   programming_model.rst
   data_model.rst
   ops/index.rst

