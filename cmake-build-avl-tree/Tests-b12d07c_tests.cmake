add_test( [==[Invalid Commands]==] /Users/josereynaldo/Documents/GitHub/AVL-Tree/cmake-build-avl-tree/Tests [==[Invalid Commands]==]  )
set_tests_properties( [==[Invalid Commands]==] PROPERTIES WORKING_DIRECTORY /Users/josereynaldo/Documents/GitHub/AVL-Tree/cmake-build-avl-tree)
add_test( [==[Edge Cases]==] /Users/josereynaldo/Documents/GitHub/AVL-Tree/cmake-build-avl-tree/Tests [==[Edge Cases]==]  )
set_tests_properties( [==[Edge Cases]==] PROPERTIES WORKING_DIRECTORY /Users/josereynaldo/Documents/GitHub/AVL-Tree/cmake-build-avl-tree)
add_test( Rotations /Users/josereynaldo/Documents/GitHub/AVL-Tree/cmake-build-avl-tree/Tests Rotations  )
set_tests_properties( Rotations PROPERTIES WORKING_DIRECTORY /Users/josereynaldo/Documents/GitHub/AVL-Tree/cmake-build-avl-tree)
add_test( Deletion /Users/josereynaldo/Documents/GitHub/AVL-Tree/cmake-build-avl-tree/Tests Deletion  )
set_tests_properties( Deletion PROPERTIES WORKING_DIRECTORY /Users/josereynaldo/Documents/GitHub/AVL-Tree/cmake-build-avl-tree)
add_test( [==[Large Insert and Remove]==] /Users/josereynaldo/Documents/GitHub/AVL-Tree/cmake-build-avl-tree/Tests [==[Large Insert and Remove]==]  )
set_tests_properties( [==[Large Insert and Remove]==] PROPERTIES WORKING_DIRECTORY /Users/josereynaldo/Documents/GitHub/AVL-Tree/cmake-build-avl-tree)
set( Tests_TESTS [==[Invalid Commands]==] [==[Edge Cases]==] Rotations Deletion [==[Large Insert and Remove]==])
