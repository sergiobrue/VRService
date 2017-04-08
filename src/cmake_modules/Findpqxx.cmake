# Sergio Perez (C) 2017

FIND_PATH(PQ_INCLUDE_DIR pq.h
  HINTS
  $ENV{PQ_DIR}
  $ENV{PQXX_DIR}
  PATH_SUFFIXES include/pq include
  PATHS
  /usr/local/include/pq
  /usr/include/pqxx
  /opt
)

FIND_LIBRARY(PQ_LIBRARY
  NAMES pq
  HINTS
  $ENV{PQ_DIR}
  $ENV{PQXX_DIR}
  PATH_SUFFIXES lib64 lib
  PATHS
  /opt
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(pq
                                  REQUIRED_VARS PQ_LIBRARY)

if (PQ_LIBRARY)
  set(PQ_FOUND TRUE)
endif (PQ_LIBRARY)

if (NOT PQ_FOUND)
  message(FATAL_ERROR "pq library not found")
endif (NOT PQ_FOUND)

FIND_PATH(PQXX_INCLUDE_DIR pqxx
  HINTS
  $ENV{PQXX_DIR}
  PATH_SUFFIXES include/pqxx include
  PATHS
  /usr/local/include/pqxx
  /usr/include/pqxx
  /opt
)

FIND_LIBRARY(PQXX_LIBRARY
  NAMES pqxx
  HINTS
  $ENV{PQXX_DIR}
  PATH_SUFFIXES lib64 lib
  PATHS
  /opt
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(pqxx
                                  REQUIRED_VARS PQXX_LIBRARY PQXX_INCLUDE_DIR)
set(PQXX_LIBRARY "${PQXX_LIBRARY} ${PQ_LIBRARY}")
