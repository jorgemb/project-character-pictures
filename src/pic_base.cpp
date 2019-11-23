#include <picture/pic_base.hpp>
#include <algorithm>
#include <utility>

using std::ostream;
using std::vector;
using std::string;
using std::shared_ptr;
using std::max;
using std::for_each;

void PicBase::pad_line(ostream &os, PicBase::size_type start, PicBase::size_type end) {
    while (start != end) {
        os << " ";
        ++start;
    }
}

StringPicture::StringPicture(vector<string> lines) : mData(std::move(lines)) {}

PicBase::size_type StringPicture::width() const {
    // Check which string is the largest
    size_type largest = 0;
    for_each(mData.begin(), mData.end(),
                  [&largest](const string &str) { largest = max(largest, str.size()); });

    return largest;
}

PicBase::size_type StringPicture::height() const {
    // Return the amount of lines
    return mData.size();
}

void StringPicture::display(ostream &os, PicBase::size_type row, bool pad) const {
    size_type last_char = 0;

    // Write the row if in range
    if (row < height()) {
        os << mData[row];
        last_char = mData[row].size();
    }

    // Pad if necessary
    if (pad) {
        pad_line(os, last_char, width());
    }
}

FramePicture::FramePicture(shared_ptr<PicBase> picture, int spaces, char frame)
        : mPicture(std::move(picture)),
          mSpaces(spaces),
          mFrame(frame) {}

PicBase::size_type FramePicture::width() const {
    return 2 + 2 * mSpaces + mPicture->width();
}

PicBase::size_type FramePicture::height() const {
    return 2 + 2 * mSpaces + mPicture->height();
}

void FramePicture::display(ostream &os, PicBase::size_type row, bool pad) const {
    // Check if out of range
    if (row >= height()) {
        if (pad)
            pad_line(os, 0, width());
        return;
    }

    // Check which part of the frame is being done
    int space_region = 1 + mSpaces;
    if (row == 0 || row == height() - 1) {
        // TOP OR BOTTOM
        os << string(width(), mFrame);
    } else if (row < space_region || row >= height() - space_region) {
        // SPACE REGION
        os << mFrame;
        pad_line(os, 1, width() - 1);
        os << mFrame;
    } else {
        // ROW OF PICTURE
        os << mFrame << string(mSpaces, ' ');
        mPicture->display(os, row - space_region, true);
        os << string(mSpaces, ' ') << mFrame;
    }
}

VCatPicture::VCatPicture(shared_ptr<PicBase> upper, shared_ptr<PicBase> lower) :
        mUpper(std::move(upper)), mLower(std::move(lower)) {}

PicBase::size_type VCatPicture::width() const {
    return max(mUpper->width(), mLower->width());
}

PicBase::size_type VCatPicture::height() const {
    return mUpper->height() + mLower->height();
}

void VCatPicture::display(ostream &os, PicBase::size_type row, bool pad) const {
    size_type last_char = 0;

    // Check if we are in the upper or lower part
    if (row < mUpper->height()) {
        mUpper->display(os, row, pad);
        last_char = mUpper->width();
    } else if (row < height()) {
        mLower->display(os, row - mUpper->height(), pad);
        last_char = mLower->width();
    }

    // Check if padding is needed
    if (pad)
        pad_line(os, last_char, width());
}

HCatPicture::HCatPicture(shared_ptr<PicBase> left, shared_ptr<PicBase> right)
        : mLeft(std::move(left)),
          mRight(std::move(right)) {}

PicBase::size_type HCatPicture::width() const {
    return mLeft->width() + mRight->width();
}

PicBase::size_type HCatPicture::height() const {
    return max(mLeft->height(), mRight->height());
}

void HCatPicture::display(ostream &os, PicBase::size_type row, bool pad) const {
    mLeft->display(os, row, pad || row < mRight->height());
    mRight->display(os, row, pad);
}