cmake -DCMAKE_TOOLCHAIN_FILE:FILEPATH=F:/dev/vcpkg/scripts/buildsystems/vcpkg.cmake -DVCPKG_TARGET_TRIPLET:STRING=x64-windows-static -DMSVC_STATIC=ON -G "Visual Studio 16 2019" -B "./build" .
