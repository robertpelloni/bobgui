#!/bin/bash

set -e

<<<<<<< HEAD
=======
if [[ "$MSYSTEM" == "MINGW32" ]]; then
    export MSYS2_ARCH="i686"
else
    export MSYS2_ARCH="x86_64"
fi

>>>>>>> origin/1422-gtkentry-s-minimum-width-is-hardcoded-to-150px
# Update everything
pacman --noconfirm -Suy

# Install the required packages
pacman --noconfirm -S --needed \
<<<<<<< HEAD
    ${MINGW_PACKAGE_PREFIX}-git \
    ${MINGW_PACKAGE_PREFIX}-cc \
    ${MINGW_PACKAGE_PREFIX}-ccache \
    ${MINGW_PACKAGE_PREFIX}-pkgconf \
    ${MINGW_PACKAGE_PREFIX}-gobject-introspection \
    ${MINGW_PACKAGE_PREFIX}-meson \
    ${MINGW_PACKAGE_PREFIX}-adwaita-icon-theme \
    ${MINGW_PACKAGE_PREFIX}-atk \
    ${MINGW_PACKAGE_PREFIX}-cairo \
    ${MINGW_PACKAGE_PREFIX}-directx-headers \
    ${MINGW_PACKAGE_PREFIX}-gdk-pixbuf2 \
    ${MINGW_PACKAGE_PREFIX}-glib2 \
    ${MINGW_PACKAGE_PREFIX}-graphene \
    ${MINGW_PACKAGE_PREFIX}-json-glib \
    ${MINGW_PACKAGE_PREFIX}-libepoxy \
    ${MINGW_PACKAGE_PREFIX}-fribidi \
    ${MINGW_PACKAGE_PREFIX}-gst-plugins-bad-libs \
    ${MINGW_PACKAGE_PREFIX}-shared-mime-info \
    ${MINGW_PACKAGE_PREFIX}-python-gobject \
    ${MINGW_PACKAGE_PREFIX}-shaderc \
    ${MINGW_PACKAGE_PREFIX}-vulkan \
    ${MINGW_PACKAGE_PREFIX}-vulkan-headers \
    ${MINGW_PACKAGE_PREFIX}-sassc
=======
    base-devel \
    git \
    mingw-w64-$MSYS2_ARCH-toolchain \
    mingw-w64-$MSYS2_ARCH-ccache \
    mingw-w64-$MSYS2_ARCH-pkg-config \
    mingw-w64-$MSYS2_ARCH-gobject-introspection \
    mingw-w64-$MSYS2_ARCH-adwaita-icon-theme \
    mingw-w64-$MSYS2_ARCH-atk \
    mingw-w64-$MSYS2_ARCH-cairo \
    mingw-w64-$MSYS2_ARCH-gdk-pixbuf2 \
    mingw-w64-$MSYS2_ARCH-glib2 \
    mingw-w64-$MSYS2_ARCH-json-glib \
    mingw-w64-$MSYS2_ARCH-libepoxy \
    mingw-w64-$MSYS2_ARCH-pango \
    mingw-w64-$MSYS2_ARCH-shared-mime-info \
    mingw-w64-$MSYS2_ARCH-gtk-doc
>>>>>>> origin/1422-gtkentry-s-minimum-width-is-hardcoded-to-150px

mkdir -p _ccache
export CCACHE_BASEDIR="$(pwd)"
export CCACHE_DIR="${CCACHE_BASEDIR}/_ccache"
<<<<<<< HEAD
export COMMON_MESON_FLAGS="-Dwerror=true -Dcairo:werror=false -Dgi-docgen:werror=false -Dgraphene:werror=false -Dlibepoxy:werror=false -Dlibsass:werror=false -Dpango:werror=false -Dsassc:werror=false -Dgdk-pixbuf:werror=false -Dglib:werror=false -Dlibcloudproviders:werror=false -Dlibpng:werror=false -Dlibtiff:werror=false -Dsysprof:werror=false -Dwayland:werror=false -Dwayland-protocols:werror=false -Dharfbuzz:werror=false -Dfreetype2:werror=false -Dfontconfig:werror=false -Dfribidi:werror=false -Dlibffi:werror=false -Dlibjpeg-turbo:werror=false -Dmutest:werror=false -Dpcre2:werror=false -Dpixman:werror=false -Dproxy-libintl:werror=false"
=======
export CC="ccache gcc"
>>>>>>> origin/1422-gtkentry-s-minimum-width-is-hardcoded-to-150px

# Build
ccache --zero-stats
ccache --show-stats
<<<<<<< HEAD
export CCACHE_DISABLE=true
meson setup \
    ${COMMON_MESON_FLAGS} \
    -Dx11-backend=false \
    -Dwayland-backend=false \
    -Dwin32-backend=true \
    -Dintrospection=enabled \
    _build
unset CCACHE_DISABLE

ninja -C _build
ccache --show-stats

tar zcf _build/bobguidll.tar.gz _build/bobgui/libbobgui*.dll
=======

./autogen.sh
make -j4

ccache --show-stats
>>>>>>> origin/1422-gtkentry-s-minimum-width-is-hardcoded-to-150px
