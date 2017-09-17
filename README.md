# gmd-tree-library: STL-like Tree Library for C++

**gmd-tree-library** is a templated container library built in C++. It contains several types of trees, acting as replacements for the *set*, *multiset*, *map*, and *multimap* containers of the STL. Its public interface is similar to the one found in the STL, with some extra functionality, specially on type conversion and iterators.

## Usage

**Requirements:** To use this library, a C++17 version of the compiler is required.

This library adopts the single include policy. To use it, download the [latest release](https://github.com/gmardau/gmd-tree-library/releases) and place *src/* and *tree* in the desired location. Everything else can be removed. Finally, include the file *tree* in your project.

[**API Reference**](https://github.com/gmardau/gmd-tree-library/blob/master/docs/wiki/tree.md)

**Examples:** Example files can be found in docs/examples.

## Future Development

At the time of writing, the library contains only Binary trees. In future releases this library is expected to include Space Partitioning trees (namely KD-trees and Orthrees (n-analogue of quadtrees)) and B-trees.

## License

**gmd-tree-library** is released under the [GNU General Public License v3.0](https://github.com/gmardau/gmd-tree-library/blob/master/LICENSE).
