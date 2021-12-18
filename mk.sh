DIR="$( cd "$( dirname "$(readlink -f "$0")" )" > /dev/null && pwd )"
if test -e "$DIR/../../../build.sh"; then
    sh "$DIR/../../../build.sh" make "$@"
elif test -e "$SHPATH"; then
    sh "$SHPATH" make "$@"
else
    make "$@"
fi
