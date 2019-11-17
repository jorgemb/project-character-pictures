#include "picture/picture.hpp"
#include <algorithm>

void PicBase::pad_line(std::ostream &os, PicBase::size_type start, PicBase::size_type end) {
    while (start != end) {
        os << " ";
        ++start;
    }
}

StringPicture::StringPicture(std::vector<std::string> lines) : mData(lines) {}

PicBase::size_type StringPicture::width() const {
    // Check which string is the largest
    size_type largest = 0;
    std::for_each(mData.begin(), mData.end(),
                  [&largest](const std::string &str) { largest = std::max(largest, str.size()); });

    return largest;
}

PicBase::size_type StringPicture::height() const {
    // Return the amount of lines
    return mData.size();
}

void StringPicture::display(std::ostream &os, PicBase::size_type row, bool pad) const {
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


std::ostream &operator<<(std::ostream &os, const Picture &picture) {
    for (int row = 0; row != picture.mPicBase->height(); ++row) {
        picture.mPicBase->display(os, row, false);
        os << std::endl;
    }

    return os;
}

Picture vcat(const Picture &top_picture, const Picture &bottom_picture) {
    std::shared_ptr<PicBase> new_picture = std::make_shared<VCatPicture>(top_picture.mPicBase, bottom_picture.mPicBase);
    return Picture(new_picture);
}

Picture hcat(const Picture &left_picture, const Picture &right_picture) {
    std::shared_ptr<PicBase> new_picture = std::make_shared<HCatPicture>(left_picture.mPicBase, right_picture.mPicBase);
    return Picture(new_picture);
}

Picture frame(const Picture &picture) {
    std::shared_ptr<PicBase> new_picture = std::make_shared<FramePicture>(picture.mPicBase);
    return Picture(new_picture);
}

Picture::Picture(const std::vector<std::string> &lines) {
    mPicBase = std::make_shared<StringPicture>(lines);
}

Picture::Picture(std::initializer_list<std::string> lines) {
    std::vector<std::string> picture_data(lines);
    mPicBase = std::make_shared<StringPicture>(picture_data);
}

Picture::Picture(std::shared_ptr<PicBase> picBase) : mPicBase(std::move(picBase)) {}

VCatPicture::VCatPicture(std::shared_ptr<PicBase> upper, std::shared_ptr<PicBase> lower) :
        mUpper(std::move(upper)), mLower(std::move(lower)) {}

PicBase::size_type VCatPicture::width() const {
    return std::max(mUpper->width(), mLower->width());
}

PicBase::size_type VCatPicture::height() const {
    return mUpper->height() + mLower->height();
}

void VCatPicture::display(std::ostream &os, PicBase::size_type row, bool pad) const {
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

HCatPicture::HCatPicture(std::shared_ptr<PicBase> left, std::shared_ptr<PicBase> right)
        : mLeft(std::move(left)),
          mRight(std::move(right)) {}

PicBase::size_type HCatPicture::width() const {
    return mLeft->width() + mRight->width();
}

PicBase::size_type HCatPicture::height() const {
    return std::max(mLeft->height(), mRight->height());
}

void HCatPicture::display(std::ostream &os, PicBase::size_type row, bool pad) const {
    mLeft->display(os, row, pad || row < mRight->height());
    mRight->display(os, row, pad);
}

FramePicture::FramePicture(std::shared_ptr<PicBase> picture, int spaces, char frame)
        : mPicture(std::move(picture)),
          mSpaces(spaces),
          mFrame(frame) {}

PicBase::size_type FramePicture::width() const {
    return 2 + 2 * mSpaces + mPicture->width();
}

PicBase::size_type FramePicture::height() const {
    return 2 + 2 * mSpaces + mPicture->height();
}

void FramePicture::display(std::ostream &os, PicBase::size_type row, bool pad) const {
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
        os << std::string(width(), mFrame);
    } else if (row < space_region || row >= height() - space_region) {
        // SPACE REGION
        os << mFrame;
        pad_line(os, 1, width() - 1);
        os << mFrame;
    } else {
        // ROW OF PICTURE
        os << mFrame << std::string(mSpaces, ' ');
        mPicture->display(os, row - space_region, true);
        os << std::string(mSpaces, ' ') << mFrame;
    }
}
