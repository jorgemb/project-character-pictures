#include "picture/picture.hpp"
#include <algorithm>


Picture::Picture(const std::vector<std::string> &lines) {
    mPicBase = std::make_shared<StringPicture>(lines);
}

Picture::Picture(std::initializer_list<std::string> lines) {
    std::vector<std::string> picture_data(lines);
    mPicBase = std::make_shared<StringPicture>(picture_data);
}

Picture::Picture(std::shared_ptr<PicBase> picBase) : mPicBase(std::move(picBase)) {}

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

Picture frame(const Picture &picture) {
    std::shared_ptr<PicBase> new_picture = std::make_shared<FramePicture>(picture.mPicBase);
    return Picture(new_picture);
}

Picture hcat(const Picture &left_picture, const Picture &right_picture) {
    std::shared_ptr<PicBase> new_picture = std::make_shared<HCatPicture>(left_picture.mPicBase, right_picture.mPicBase);
    return Picture(new_picture);
}

