FILE(REMOVE_RECURSE
  "CMakeFiles/hello_world.dir/hello_world.c.o"
  "hello_world.pdb"
  "hello_world"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang C)
  INCLUDE(CMakeFiles/hello_world.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
