if( NOT TARGET CoC-Utils )
    get_filename_component( COC-UTILS_SOURCE_PATH "${CMAKE_CURRENT_LIST_DIR}/../../src" ABSOLUTE )

	LIST( APPEND COC-UTILS_SOURCES
		${COC-UTILS_SOURCE_PATH}/cocBounce2D.cpp
		${COC-UTILS_SOURCE_PATH}/cocBounce.cpp
		${COC-UTILS_SOURCE_PATH}/cocFboWrapper.cpp
		${COC-UTILS_SOURCE_PATH}/cocFlag.cpp
		${COC-UTILS_SOURCE_PATH}/cocGLUtils.cpp
		${COC-UTILS_SOURCE_PATH}/cocParameters.cpp
		${COC-UTILS_SOURCE_PATH}/cocPoly.cpp
		${COC-UTILS_SOURCE_PATH}/cocScaleGesture.cpp
		${COC-UTILS_SOURCE_PATH}/cocSwipe.cpp
		#${COC-UTILS_SOURCE_PATH}/cocTextBoxExtended.cpp  # causes compile error on linux
		${COC-UTILS_SOURCE_PATH}/cocTimer.cpp
		${COC-UTILS_SOURCE_PATH}/cocTween.cpp
		)

    add_library( CoC-Utils ${COC-UTILS_SOURCES} )
    target_include_directories( CoC-Utils PUBLIC "${COC-UTILS_SOURCE_PATH}" )

    # If Cinder included from this block:

    target_include_directories( CoC-Utils SYSTEM BEFORE PUBLIC "${CINDER_PATH}/include" )

    if( NOT TARGET cinder )
        include( "${CINDER_PATH}/proj/cmake/configure.cmake" )
        find_package( cinder REQUIRED PATHS
                "${CINDER_PATH}/${CINDER_LIB_DIRECTORY}"
                "$ENV{CINDER_PATH}/${CINDER_LIB_DIRECTORY}" )
    endif()

    target_link_libraries( CoC-Utils PRIVATE cinder )

    # Add CoC-Core block as a dependency
    get_filename_component( COC-CORE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../../../CoC-Core/proj/cmake" ABSOLUTE )
    find_package( CoC-Core REQUIRED PATHS "${COC-CORE_MODULE_PATH}" )
    if (CoC-Core_FOUND)
        add_dependencies( CoC-Utils CoC-Core )
        target_link_libraries( CoC-Utils PUBLIC CoC-Core)
    endif()

endif()
