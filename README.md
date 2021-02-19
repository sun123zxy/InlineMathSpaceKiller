# Inline Math Space Killer

A simple tool which removes spaces near dollar($) in inline-math.

Can be useful when using Pandoc to export some non-standard markdown with latex maths.

Should be compiled under `c++11` .

## Usage

`spaceKiller <inputFile> [-o <outputFile>|--overwrite] [--verbose]`

+ `--overwrite`: Overwrite `<inputFile>`
+ `--verbose`: Print more details.