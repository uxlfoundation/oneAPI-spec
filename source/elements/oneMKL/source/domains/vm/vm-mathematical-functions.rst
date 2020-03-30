.. _vm-mathematical-functions:

VM Mathematical Functions
=========================


.. container::


   This section describes VM functions that compute values of
   mathematical functions on real and complex vector arguments with unit
   increment.


   Each function is introduced by its short name, a brief description of
   its purpose, and the calling sequence for each type of data, as well
   as a description of the input/output arguments.


   The input range of parameters is equal to the mathematical range of
   the input data type, unless the function description specifies input
   threshold values, which mark off the precision overflow, as follows:


   -  


      .. container::
         :name: LI_BD1C9B3D061F4CAEBA02237BA30BB74C


         FLT_MAX denotes the maximum number representable in single
         precision real data type


   -  


      .. container::
         :name: LI_5B56F34431C341C1960E27ABE0B480E3


         DBL_MAX denotes the maximum number representable in double
         precision real data type


   `Table "VM Mathematical Functions" <#TBL9-2>`__ lists available
   mathematical functions and associated data types.


   .. container:: tablenoborder


      .. list-table:: 
         :header-rows: 1

         * -  Function 
           -  Data Types 
           -  Description 
         * -  `Arithmetic Functions: <arithmetic-functions.html>`__
           -
           -
         * -        `add <add.html>`__
           -  s, d, c, z 
           -  Adds vector elements 
         * -        `sub <sub.html>`__
           -  s, d, c, z 
           -  Subtracts vector elements 
         * -        `sqr <sqr.html>`__
           -  s, d 
           -  Squares vector elements 
         * -        `mul <mul.html>`__
           -  s, d, c, z 
           -  Multiplies vector elements 
         * -        `mulbyconj <mulbyconj.html>`__
           -  c, z 
           -  Multiplies elements of one vector by conjugated elements of       the second vector
         * -        `conj <conj.html>`__
           -  c, z 
           -  Conjugates vector elements 
         * -        `abs <abs.html>`__
           -  s, d, c, z 
           -  Computes the absolute value of vector elements 
         * -        `arg <arg.html>`__
           -  c, z 
           -  Computes the argument of vector elements 
         * -        `linearfrac <linearfrac.html>`__
           -  s, d 
           -  Performs linear fraction transformation of vectors 
         * -        `fmod <fmod.html>`__
           -  s, d 
           -  Performs element by element computation of the modulus       function of vector ``a`` with respect to vector ``b``
         * -        `remainder <remainder.html>`__
           -  s, d 
           -  Performs element by element computation of the remainder       function on the elements of vector ``a`` and the corresponding      elements of vector ``b``
         * -  `Power and Root Functions: <power-and-root-functions.html>`__
           -
           -
         * -        `inv <inv.html>`__
           -  s, d 
           -  Inverts vector elements 
         * -        `div <div.html>`__
           -  s, d, c, z 
           -  Divides elements of one vector by elements of the second       vector
         * -        `sqrt <sqrt.html>`__
           -  s, d, c, z 
           -  Computes the square root of vector elements 
         * -        `invsqrt <invsqrt.html>`__
           -  s, d 
           -  Computes the inverse square root of vector elements 
         * -        `cbrt <cbrt.html>`__
           -  s, d 
           -  Computes the cube root of vector elements 
         * -        `invcbrt <invcbrt.html>`__
           -  s, d 
           -  Computes the inverse cube root of vector elements 
         * -        `pow2o3 <pow2o3.html>`__
           -  s, d 
           -  Computes the cube root of the square of each vector element 
         * -        `pow3o2 <pow3o2.html>`__
           -  s, d 
           -  Computes the square root of the cube of each vector element 
         * -        `pow <pow.html>`__
           -  s, d, c, z 
           -  Raises each vector element to the specified power 
         * -        `powx <powx.html>`__
           -  s, d, c, z 
           -  Raises each vector element to the constant power 
         * -        `powr <powr.html>`__
           -  s, d 
           -  Computes ``a`` to the power ``b`` for elements of two vectors,       where the elements of vector argument ``a`` are all non-negative
         * -        `hypot <hypot.html>`__
           -  s, d 
           -  Computes the square root of sum of squares 
         * -  `Exponential and Logarithmic Functions: <exponential-and-logarithmic-functions.html>`__
           -
           -
         * -        `exp <exp.html>`__
           -  s, d, c, z 
           -  Computes the base ``e`` exponential of vector elements 
         * -        `exp2 <exp2.html>`__
           -  s, d 
           -  Computes the base 2 exponential of vector elements 
         * -        `exp10 <exp10.html>`__
           -  s, d 
           -  Computes the base 10 exponential of vector elements 
         * -        `expm1 <expm1.html>`__
           -  s, d 
           -  Computes the base ``e`` exponential of vector elements       decreased by 1
         * -        `ln <ln.html>`__
           -  s, d, c, z 
           -  Computes the natural logarithm of vector elements 
         * -        `log2 <log2.html>`__
           -  s, d 
           -  Computes the base 2 logarithm of vector elements 
         * -        `log10 <log10.html>`__
           -  s, d, c, z 
           -  Computes the base 10 logarithm of vector elements 
         * -        `log1p <log1p.html>`__
           -  s, d 
           -  Computes the natural logarithm of vector elements that are       increased by 1
         * -        `logb <logb.html>`__
           -  s, d 
           -  Computes the exponents of the elements of input vector ``a`` 
         * -  `Trigonometric Functions: <trigonometric-functions.html>`__
           -
           -
         * -        `cos <cos.html>`__
           -  s, d, c, z 
           -  Computes the cosine of vector elements 
         * -        `sin <sin.html>`__
           -  s, d, c, z 
           -  Computes the sine of vector elements 
         * -        `sincos <sincos.html>`__
           -  s, d 
           -  Computes the sine and cosine of vector elements 
         * -        `cis <cis.html>`__
           -  c, z 
           -  Computes the complex exponent of vector elements (cosine and       sine combined to complex value)
         * -        `tan <tan.html>`__
           -  s, d, c, z 
           -  Computes the tangent of vector elements 
         * -        `acos <acos.html>`__
           -  s, d, c, z 
           -  Computes the inverse cosine of vector elements 
         * -        `asin <asin.html>`__
           -  s, d, c, z 
           -  Computes the inverse sine of vector elements 
         * -        `atan <atan.html>`__
           -  s, d, c, z 
           -  Computes the inverse tangent of vector elements 
         * -        `atan2 <atan2.html>`__
           -  s, d 
           -  Computes the four-quadrant inverse tangent of ratios of the       elements of two vectors
         * -        `cospi <cospi.html>`__
           -  s, d 
           -  Computes the cosine of vector elements multiplied by ``π`` 
         * -        `sinpi <sinpi.html>`__
           -  s, d 
           -  Computes the sine of vector elements multiplied by ``π`` 
         * -        `tanpi <tanpi.html>`__
           -  s, d 
           -  Computes the tangent of vector elements multiplied by ``π`` 
         * -        `acospi <acospi.html>`__
           -  s, d 
           -  Computes the inverse cosine of vector elements divided by       ``π``
         * -        `asinpi <asinpi.html>`__
           -  s, d 
           -  Computes the inverse sine of vector elements divided by ``π`` 
         * -        `atanpi <atanpi.html>`__
           -  s, d 
           -  Computes the inverse tangent of vector elements divided by       ``π``
         * -        `atan2pi <atan2pi.html>`__
           -  s, d 
           -  Computes the four-quadrant inverse tangent of the ratios of the corresponding elements of two vectors divided by ``π``
         * -        `cosd <cosd.html>`__
           -  s, d 
           -  Computes the cosine of vector elements multiplied by ``π``/180 
         * -        `sind <sind.html>`__
           -  s, d 
           -  Computes the sine of vector elements multiplied by ``π``/180 
         * -        `tand <tand.html>`__
           -  s, d 
           -  Computes the tangent of vector elements multiplied by       ``π``/180
         * -  `Hyperbolic Functions: <hyperbolic-functions.html>`__
           -
           -
         * -        `cosh <cosh.html>`__
           -  s, d, c, z 
           -  Computes the hyperbolic cosine of vector elements 
         * -        `sinh <sinh.html>`__
           -  s, d, c, z 
           -  Computes the hyperbolic sine of vector elements 
         * -        `tanh <tanh.html>`__
           -  s, d, c, z 
           -  Computes the hyperbolic tangent of vector elements 
         * -        `acosh <acosh.html>`__
           -  s, d, c, z 
           -  Computes the inverse hyperbolic cosine of vector elements 
         * -        `asinh <asinh.html>`__
           -  s, d, c, z 
           -  Computes the inverse hyperbolic sine of vector elements 
         * -        `atanh <atanh.html>`__
           -  s, d, c, z 
           -  Computes the inverse hyperbolic tangent of vector elements. 
         * -  `Special Functions: <special-functions.html>`__
           -
           -
         * -        `erf <erf.html>`__
           -  s, d 
           -  Computes the error function value of vector elements 
         * -        `erfc <erfc.html>`__
           -  s, d 
           -  Computes the complementary error function value of vector       elements
         * -        `cdfnorm <cdfnorm.html>`__
           -  s, d 
           -  Computes the cumulative normal distribution function value of       vector elements
         * -        `erfinv <erfinv.html>`__
           -  s, d 
           -  Computes the inverse error function value of vector elements 
         * -        `erfcinv <erfcinv.html>`__
           -  s, d 
           -  Computes the inverse complementary error function value of       vector elements
         * -        `cdfnorminv <cdfnorminv.html>`__
           -  s, d 
           -  Computes the inverse cumulative normal distribution function       value of vector elements
         * -        `lgamma <lgamma.html>`__
           -  s, d 
           -  Computes the natural logarithm for the absolute value of the       gamma function of vector elements
         * -        `tgamma <tgamma.html>`__
           -  s, d 
           -  Computes the gamma function of vector elements 
         * -        `expint1 <expint1.html>`__
           -  s, d 
           -  Computes the exponential integral of vector elements 
         * -  `Rounding Functions: <rounding-functions.html>`__
           -
           -
         * -        `floor <floor.html>`__
           -  s, d 
           -  Rounds towards minus infinity 
         * -        `ceil <ceil.html>`__
           -  s, d 
           -  Rounds towards plus infinity 
         * -        `trunc <trunc.html>`__
           -  s, d 
           -  Rounds towards zero infinity 
         * -        `round <round.html>`__
           -  s, d 
           -  Rounds to nearest integer 
         * -        `nearbyint <nearbyint.html>`__
           -  s, d 
           -  Rounds according to current mode 
         * -        `rint <rint.html>`__
           -  s, d 
           -  Rounds according to current mode and raising inexact result       exception
         * -        `modf <modf.html>`__
           -  s, d 
           -  Computes the integer and fractional parts 
         * -        `frac <frac.html>`__
           -  s, d 
           -  Computes the fractional part 
         * -  `Miscellaneous Functions: <miscellaneous-vm-functions.html>`__
           -
           -
         * -        `copysign <copysign.html>`__
           -  s, d 
           -  Returns vector of elements of one argument with signs changed       to match other argument elements
         * -        `nextafter <nextafter.html>`__
           -  s, d 
           -  Returns vector of elements containing the next representable       floating-point values following the values from the elements of      one vector in the direction of the corresponding elements of      another vector
         * -        `fdim <fdim.html>`__
           -  s, d 
           -  Returns vector containing the differences of the corresponding       elements of the vector arguments if the first is larger and +0      otherwise
         * -        `fmax <fmax.html>`__
           -  s, d 
           -  Returns the larger of each pair of elements of the two vector       arguments
         * -        `fmin <fmin.html>`__
           -  s, d 
           -  Returns the smaller of each pair of elements of the two vector       arguments
         * -        `maxmag <maxmag.html>`__
           -  s, d 
           -  Returns the element with the larger magnitude between each       pair of elements of the two vector arguments
         * -        `minmag <minmag.html>`__
           -  s, d 
           -  Returns the element with the smaller magnitude between each       pair of elements of the two vector arguments


**Parent topic:** :ref:`onemkl_vm`

.. toctree::
    :hidden:

    arithmetic-functions
    power-and-root-functions
    exponential-and-logarithmic-functions
    trigonometric-functions
    hyperbolic-functions
    special-functions
    rounding-functions
