# MAX_PURE

API version: [**v0**](../../v0.md)

## Note

MAX_PURE allows a developer to provide aliasing information to the compiler.
A developer will want to be familiar with [pointer aliasing optimizations](AliasingOptimizations.md) in order to use MAX_PURE.

A pure function is one that references or modifies only locals and arguments.
It cannot follow first-level indirections. This means no pointers or references.
A pure function also cannot access globals.

Use [MAX_PURE_WITH_GLOBALS](MAX_PURE_WITH_GLOBALS.md) instead if the code needs to access globals.

Use [MAX_SEMI_PURE](MAX_SEMI_PURE.md) instead if the code needs to follow first-level indirections.

## Example

```c++
template< typename T >
MAX_PURE( inline T Max( const T lhs, const T rhs ) );
```

## Implementation

Go to [the implementation](../../../../Code/Include/max/Compiling/AliasingOptimizations.hpp#L10).