# Automatically generated by scripts/boost/generate-ports.ps1

vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO boostorg/variant
    REF boost-${VERSION}
    SHA512 5b998ef2a9668ff9d6f8f698060493ff208f741953d0252ac94d0733d2ba36571d02ecb8e19a9263009252475451ad5a5baf4b114c6074a442304c91512a4378
    HEAD_REF master
)

include(${CURRENT_INSTALLED_DIR}/share/boost-vcpkg-helpers/boost-modular-headers.cmake)
boost_modular_headers(SOURCE_PATH ${SOURCE_PATH})
