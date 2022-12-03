#pragma once

#include <string>
#include <iostream>

///////////////////////////////////////
// C++ utilities for Advent of Code. //
///////////////////////////////////////


// `LineIterator` obtains and stores a line from the given stream
// (std::cin for example) with `std::getline`. `IstreamLines` is
// a lazy view based on `LineIterator<std::istream>`.
//
// Usage:
//
//     for (const std::string& line : IstreamLines{}) {
//       ...
//     }
//     for (std::string_view line : IstreamLines{}) {
//       ...
//     }

template <typename Stream>
class LineIterator {
public:
    LineIterator(Stream& stream, bool end = false)
        : stream_(&stream), end_(end) {
        ++(*this);
    }
    LineIterator(const LineIterator&) = default;
    LineIterator(LineIterator&&) = default;
    LineIterator& operator=(const LineIterator&) = default;
    LineIterator& operator=(LineIterator&&) = default;
    ~LineIterator() = default;

    LineIterator& operator++() {
        if (!end_) {
            end_ = !std::getline(*stream_, current_);
        }
        return *this;
    }

    LineIterator operator++(int) {
        LineIterator curr = *this;
        ++(*this);
        return curr;
    }

    const std::string& operator*() const {
        return current_;
    }

    bool operator==(const LineIterator& other) {
        return end_ == other.end_ && stream_ == other.stream_;
    }

private:
    Stream* stream_ = nullptr;
    std::string current_;
    bool end_ = false;
};

using IstreamLineIterator = LineIterator<std::istream>;

struct IstreamLines {
public:
    auto begin() const { return begin_; }
    auto end() const { return end_; }

private:
    IstreamLineIterator begin_{std::cin};
    const IstreamLineIterator end_{std::cin, /*end*/ true};
};
