#!/bin/bash
glslangValidator -V -o triangle.vert.spv triangle.vert
glslangValidator -V -o triangle.frag.spv triangle.frag
mkdir -p ../assets/shaders
mv triangle.vert.spv ../assets/shaders/triangle_vert.spv
mv triangle.frag.spv ../assets/shaders/triangle_frag.spv
