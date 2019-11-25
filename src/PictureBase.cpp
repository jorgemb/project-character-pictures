#include <picture/PictureBase.hpp>
#include <algorithm>
#include <utility>

using std::ostream;
using std::vector;
using std::string;
using std::shared_ptr;
using std::max;
using std::for_each;

void PictureBase::padLine(ostream &ostream, PictureBase::size_type start, PictureBase::size_type end) {
    while (start != end) {
        ostream << " ";
        ++start;
    }
}

StringPicture::StringPicture(vector<string> lines) : mData(std::move(lines)) {}

PictureBase::size_type StringPicture::getWidth() const {
    // Check which string is the largest
    size_type largest = 0;
    for_each(mData.begin(), mData.end(),
             [&largest](const string &str) { largest = max(largest, str.size()); });

    return largest;
}

PictureBase::size_type StringPicture::getHeight() const {
    // Return the amount of lines
    return mData.size();
}

void StringPicture::display(ostream &os, PictureBase::size_type row, bool pad) const {
    size_type last_char = 0;

    // Write the row if in range
    if (row < getHeight()) {
        os << mData[row];
        last_char = mData[row].size();
    }

    // Pad if necessary
    if (pad) {
        padLine(os, last_char, getWidth());
    }
}

FramePicture::FramePicture(shared_ptr<PictureBase> picture, int spaces, char frame)
        : mPicture(std::move(picture)),
          mSpaces(spaces),
          mFrame(frame) {}

PictureBase::size_type FramePicture::getWidth() const {
    return 2 + 2 * mSpaces + mPicture->getWidth();
}

PictureBase::size_type FramePicture::getHeight() const {
    return 2 + 2 * mSpaces + mPicture->getHeight();
}

void FramePicture::display(ostream &os, PictureBase::size_type row, bool pad) const {
    // Check if out of range
    if (row >= getHeight()) {
        if (pad)
            padLine(os, 0, getWidth());
        return;
    }

    // Check which part of the frame is being done
    int space_region = 1 + mSpaces;
    if (row == 0 || row == getHeight() - 1) {
        // TOP OR BOTTOM
        os << string(getWidth(), mFrame);
    } else if (row < space_region || row >= getHeight() - space_region) {
        // SPACE REGION
        os << mFrame;
        padLine(os, 1, getWidth() - 1);
        os << mFrame;
    } else {
        // ROW OF PICTURE
        os << mFrame << string(mSpaces, ' ');
        mPicture->display(os, row - space_region, true);
        os << string(mSpaces, ' ') << mFrame;
    }
}

VCatPicture::VCatPicture(shared_ptr<PictureBase> upper, shared_ptr<PictureBase> lower) :
        mUpper(std::move(upper)), mLower(std::move(lower)) {}

PictureBase::size_type VCatPicture::getWidth() const {
    return max(mUpper->getWidth(), mLower->getWidth());
}

PictureBase::size_type VCatPicture::getHeight() const {
    return mUpper->getHeight() + mLower->getHeight();
}

void VCatPicture::display(ostream &os, PictureBase::size_type row, bool pad) const {
    size_type last_char = 0;

    // Check if we are in the upper or lower part
    if (row < mUpper->getHeight()) {
        mUpper->display(os, row, pad);
        last_char = mUpper->getWidth();
    } else if (row < getHeight()) {
        mLower->display(os, row - mUpper->getHeight(), pad);
        last_char = mLower->getWidth();
    }

    // Check if padding is needed
    if (pad)
        padLine(os, last_char, getWidth());
}

HCatPicture::HCatPicture(shared_ptr<PictureBase> left, shared_ptr<PictureBase> right)
        : mLeft(std::move(left)),
          mRight(std::move(right)) {}

PictureBase::size_type HCatPicture::getWidth() const {
    return mLeft->getWidth() + mRight->getWidth();
}

PictureBase::size_type HCatPicture::getHeight() const {
    return max(mLeft->getHeight(), mRight->getHeight());
}

void HCatPicture::display(ostream &os, PictureBase::size_type row, bool pad) const {
    mLeft->display(os, row, pad || row < mRight->getHeight());
    mRight->display(os, row, pad);
}