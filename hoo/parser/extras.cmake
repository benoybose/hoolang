MACRO(ADD_HOO_PARSER_TEST xtarget)
    TARGET_INCLUDE_DIRECTORIES(${xtarget} PRIVATE 
            ${CMAKE_SOURCE_DIR}
            ${ANTLR4_INCLUDE_DIR}
            ${ANTLR4_INCLUDE_DIR_HooANTLR4})

    ADD_DEPENDENCIES(${xtarget} antlr4_static)
    TARGET_LINK_LIBRARIES(${xtarget} PRIVATE
            antlr4_static
            hooast
            hootest
            hooparser)
    ADD_TEST(${xtarget} ${xtarget})
ENDMACRO()