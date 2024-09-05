#!/usr/bin/env bash
#----------------------------------------------------------------------------
#
# Arm64 CPU system registers tools
# Copyright (c) 2023, Thierry Lelegard
# BSD-2-Clause license, see the LICENSE file.
#
# This script downloads a few Arm specifications from the Arm site.
# These specs are tarballs of JSON or XML files which are useful to
# process the description of the Arm ISA or registers.
#
#----------------------------------------------------------------------------

SCRIPT=$(basename $0)
SCRIPTDIR=$(cd $(dirname $0); pwd)
info()  { echo >&2 "$SCRIPT: $*"; }
error() { echo >&2 "$SCRIPT: $*"; exit 1; }
usage() { echo >&2 "invalid command, try \"$SCRIPT --help\""; exit 1; }

# Default values for command line options.
BASE_URL="https://developer.arm.com/downloads/-/exploration-tools"
TARBALL_URL=""
ISA_PREFIX="ISA_A64_xml_A_profile"
FEATURES_PREFIX="AARCHMRS_A_profile"
SYSREG_PREFIX="SysReg_xml_A_profile"
TARBALL_PREFIX=""
TARBALL_SUFFIX=".tar.gz"
FORCE_DOWNLOAD=false
OUTPUT_FILE=""
OUTPUT_DIR="$SCRIPTDIR/downloads"
LOG_OUTDIR=""
LOG_OUTFILE=""

#-----------------------------------------------------------------------------
# Display help text
#-----------------------------------------------------------------------------

showhelp()
{
    cat >&2 <<EOF

Download a tarball of Arm specifications from the Arm site.

Usage: $SCRIPT [options]

Options:

  -b <url>
  --base-url <url>
      Specify the URL of the base Web page for the Arm specs. Default:
      $BASE_URL

  -d
  --download
      Force download, even if the output tarball is already present.

  -f
  --features
      Download the specs for Arm Architecture Features.
      Same as --prefix $FEATURES_PREFIX

  -h
  --help
      Display this help text.

  -i
  --isa
      Download the specs for Arm A64 Instruction Set Architecture.
      Same as --prefix $ISA_PREFIX

  --log-outdir 'string'
      Output on stderr the full path of the directory where the tarball file
      is expanded, prefixed with the specified string.
      
  --log-outfile 'string'
      Output on stderr the full path of the downloaded tarball file,
      prefixed with the specified string.
      
  -o
  --output
      Output file. By default, use the file name from the URL.
      Directory will be created if non-existent.

  -p
  --prefix
      Unique prefix of the tarball to locate in the base Web page.

  -s
  --sysreg
      Download the specs for Arm Architecture System Registers.
      Same as --prefix $SYSREG_PREFIX

  -u <url>
  --url <url>
      Specify the URL of the target tarball. By default, try to find it in
      the base Web page (see --base-url).

EOF
    exit 1
}

#-----------------------------------------------------------------------------
# Decode command line arguments
#-----------------------------------------------------------------------------

while [[ $# -gt 0 ]]; do
    case "$1" in
        -b|--base-url)
            [[ $# -gt 1 ]] || usage; shift
            BASE_URL="$1"
            ;;
        -d|--download)
            FORCE_DOWNLOAD=true
            ;;
        -f|--features)
            TARBALL_PREFIX="$FEATURES_PREFIX"
            ;;
        -h|--help)
            showhelp
            ;;
        -i|--isa)
            TARBALL_PREFIX="$ISA_PREFIX"
            ;;
        --log-outdir)
            [[ $# -gt 1 ]] || usage; shift
            LOG_OUTDIR="$1"
            ;;
        --log-outfile)
            [[ $# -gt 1 ]] || usage; shift
            LOG_OUTFILE="$1"
            ;;
        -o|--output)
            [[ $# -gt 1 ]] || usage; shift
            OUTPUT_FILE="$1"
            ;;
        -p|--prefix)
            [[ $# -gt 1 ]] || usage; shift
            TARBALL_PREFIX="$1"
            ;;
        -s|--sysreg)
            TARBALL_PREFIX="$SYSREG_PREFIX"
            ;;
        -u|--url)
            [[ $# -gt 1 ]] || usage; shift
            TARBALL_URL="$1"
            ;;
        *)
            usage
            ;;
    esac
    shift
done

if [[ -z "$TARBALL_URL" && -z "$TARBALL_PREFIX" ]]; then
    error "nothing to download, try --help"
fi

#-----------------------------------------------------------------------------
# Get tarball
#-----------------------------------------------------------------------------

# Get URL up to host part.
url_host() {
    sed <<<$1 -e 's|^\([[:alnum:]]*://[^/]*\).*$|\1|'
}

# Get URL up to directory part.
url_dir() {
    sed <<<$1 -e 's|/[^/]*$||'
}

# Get file name from URL
url_file() {
    sed <<<$1 -e 's|.*/||' -e 's|[&#].*$||'
}

# Resolve URL from base and relative URL.
resolve_url() {
    local base="$1"
    local rel="$2"
    if grep -q <<<$rel '^[[:alnum:]]*:'; then
        base=""
    elif [[ $rel == /* ]]; then
        base=$(url_host "$base")
    else
        base=$(url_dir "$base")/
    fi
    echo "$base$rel"
}

# Check if file is already downloaded.
need_download() {
    if ! $FORCE_DOWNLOAD && [[ -n "$OUTPUT_FILE" && -e "$OUTPUT_FILE" ]]; then
        info "$OUTPUT_FILE already downloaded"
        return 1
    else
        return 0
    fi
}

# Try to locate Chrome browser.
get_chrome() {
    local chrome=$(which chrome-browser 2>/dev/null)
    [[ -z "$chrome" ]] && chrome=$(which chromium-browser 2>/dev/null)
    [[ -z "$chrome" ]] && chrome=$(which chrome 2>/dev/null)
    [[ -z "$chrome" ]] && chrome=$(which chromium 2>/dev/null)
    if [[ -z "$chrome" && $(uname -s) == Darwin ]]; then
        local app="/Applications/Google Chrome.app/Contents/MacOS/Google Chrome"
        [[ -x "$app" ]] && chrome="$app"
    fi
    [[ -n "$chrome" ]] && echo "$chrome"
}

# Locate the tarball URL in an HTML page as input.
grep_tarball_url() {
    grep "href=\"[^\"]*/$TARBALL_PREFIX[^\"]*$TARBALL_SUFFIX\"" |
        sed -e "s|.*href=\"\\([^\"]*/$TARBALL_PREFIX\\)|\\1|" -e 's|".*||' |
        head -1
}
    
# Output file.
[[ -z "$OUTPUT_FILE" && -n "$TARBALL_URL" ]] && OUTPUT_FILE="$OUTPUT_DIR/"$(url_file "$TARBALL_URL")

# Get URL of SysReg tarball at arm.com.
if need_download && [[ -z "$TARBALL_URL" ]]; then
    # Try directly from base URL response.
    # This used to work in the past but now the page is generated from JavaScript in the response.
    TARBALL_URL=$(curl -sSL "$BASE_URL" | grep_tarball_url)
    if [[ -z "$TARBALL_URL" ]]; then
        CHROME=$(get_chrome)
        if [[ -n "$CHROME" ]]; then
            info "URL not found in base URL, using Chrome to generate the page"
            TARBALL_URL=$("$CHROME" --headless --dump-dom "$BASE_URL" | grep_tarball_url)
        fi
    fi
    [[ -z "$TARBALL_URL" ]] && error "$TARBALL_PREFIX*$TARBALL_SUFFIX not found in $BASE_URL, try option --url"
    TARBALL_URL=$(resolve_url "$BASE_URL" "$TARBALL_URL")
fi

# Download and expand the tarball.
[[ -z "$OUTPUT_FILE" ]] && OUTPUT_FILE="$OUTPUT_DIR/"$(url_file "$TARBALL_URL")
OUTPUT_DIR=$(dirname "$OUTPUT_FILE")
mkdir -p "$OUTPUT_DIR"

if need_download; then
    info "downloading $TARBALL_URL ..."
    curl -sSL "$TARBALL_URL" -o "$OUTPUT_FILE"
    [[ -e "$OUTPUT_FILE" ]] || error "error downloading $OUTPUT_FILE"
fi

EXPAND_DIR="$OUTPUT_DIR"/$(basename "$OUTPUT_FILE" $TARBALL_SUFFIX | sed -e 's|\.gz$||' -e 's|\.tar$||' -e 's|\.tgz$||')
mkdir -p "$EXPAND_DIR"

info "expanding $OUTPUT_FILE ..."
tar xzf "$OUTPUT_FILE" -C "$EXPAND_DIR"

[[ -n "$LOG_OUTDIR" ]] && echo >&2 "$LOG_OUTDIR"$(realpath "$EXPAND_DIR")
[[ -n "$LOG_OUTFILE" ]] && echo >&2 "$LOG_OUTFILE"$(realpath "$OUTPUT_FILE")
