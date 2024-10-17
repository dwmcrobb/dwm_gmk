#!/bin/sh

# The rules of thumb, when dealing with these values are:
#
#     - Always increase the revision value.
#     - Increase the current value whenever an interface has been added,
#       removed or changed.
#     - Increase the age value only if the changes made to the ABI are
#       backward compatible.
#
# Format is "current:revision:age"

SHARED_LIB_VERSION="0:0:0"

RELEASE_NAME_FILE=`dirname $0`/latest_release
RELEASE_NAME=`cat ${RELEASE_NAME_FILE}`

GIT_TAG=""
GIT_VERSION=""
SVN_TAG=""
SVN_VERSION=""
DWM_TAG=""
DWM_VERSION=""

DwmGetGitTag() {
    local gittag=`git describe --tags --dirty 2>/dev/null`
    if test -z "${gittag}"; then
	GIT_TAG="${RELEASE_NAME}"
	GIT_VERSION=`echo ${GIT_TAG} | cut -d'-' -f2`
    else
        dirty=`echo "${gittag}" | awk -F '-' '{ if (NF > 2) { print "dirty"; } }'`
        if test -z "${dirty}"; then
	    GIT_TAG="${gittag}"
	    GIT_VERSION=`echo "${gittag}" | awk -F '-' '{print $NF}'`
        else
	    fakevers=`date +%Y%m%d`
	    GIT_TAG="$1-0.0.${fakevers}"
	    GIT_VERSION="0.0.${fakevers}"
        fi
    fi
}

DwmGetTag() {
    DwmGetGitTag $1
    if test -n "${GIT_TAG}"; then
	DWM_TAG="${GIT_TAG}"
	DWM_VERSION="${GIT_VERSION}"
    fi
    if test -z "${DWM_TAG}" ; then
	DWM_TAG="$1-0.0.0"
	DWM_VERSION="0.0.0"
    fi
}

DwmGetTag dwmgmk

args=`getopt sv $*`
set -- $args
for i; do
    case "$i" in
	-s)
	    echo "${SHARED_LIB_VERSION}"
	    exit 0
	    break;;
	-v)
	    echo "${DWM_VERSION}"
	    exit 0
	    break;;
    esac
done

echo "${DWM_TAG}"
