#!/bin/bash
# Quick C++ documentation lookup script for cppreference.com

if [ $# -eq 0 ]; then
    echo "Usage: ./cpp_doc.sh <function_name>"
    echo ""
    echo "Examples:"
    echo "  ./cpp_doc.sh getline"
    echo "  ./cpp_doc.sh vector"
    echo "  ./cpp_doc.sh string"
    echo "  ./cpp_doc.sh map"
    echo "  ./cpp_doc.sh ifstream"
    echo ""
    echo "Opens cppreference.com documentation in your browser"
    exit 1
fi

FUNC="$1"

# Common direct mappings to specific pages
case "$FUNC" in
    "getline")
        URL="https://en.cppreference.com/w/cpp/string/basic_string/getline"
        ;;
    "vector")
        URL="https://en.cppreference.com/w/cpp/container/vector"
        ;;
    "string")
        URL="https://en.cppreference.com/w/cpp/string/basic_string"
        ;;
    "map")
        URL="https://en.cppreference.com/w/cpp/container/map"
        ;;
    "ifstream")
        URL="https://en.cppreference.com/w/cpp/io/basic_ifstream"
        ;;
    "ofstream")
        URL="https://en.cppreference.com/w/cpp/io/basic_ofstream"
        ;;
    "cout")
        URL="https://en.cppreference.com/w/cpp/io/cout"
        ;;
    "cin")
        URL="https://en.cppreference.com/w/cpp/io/cin"
        ;;
    "find")
        URL="https://en.cppreference.com/w/cpp/algorithm/find"
        ;;
    *)
        # Default: search for it
        URL="https://en.cppreference.com/mwiki/index.php?search=std::${FUNC}"
        ;;
esac

echo "📖 Opening documentation for: $FUNC"
echo "🔗 $URL"
echo ""

# Open in default browser
if command -v open &> /dev/null; then
    # macOS
    open "$URL"
elif command -v xdg-open &> /dev/null; then
    # Linux
    xdg-open "$URL"
elif command -v start &> /dev/null; then
    # Windows
    start "$URL"
else
    echo "Please visit: $URL"
fi

