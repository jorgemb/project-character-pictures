#include "picture/Picture.hpp"
#include <algorithm>


Picture::Picture(const std::vector<std::string> &lines) {
    mPicBase = std::make_shared<StringPicture>(lines);
}

Picture::Picture(std::initializer_list<std::string> lines) {
    std::vector<std::string> PictureData(lines);
    mPicBase = std::make_shared<StringPicture>(PictureData);
}

Picture::Picture(std::shared_ptr<PictureBase> picBase) : mPicBase(std::move(picBase)) {}

std::ostream &operator<<(std::ostream &os, const Picture &picture) {
    for (int row = 0; row != picture.mPicBase->getHeight(); ++row) {
        picture.mPicBase->display(os, row, false);
        os << std::endl;
    }

    return os;
}

Picture vcat(const Picture &TopPicture, const Picture &BottomPicture) {
    std::shared_ptr<PictureBase> NewPicture = std::make_shared<VCatPicture>(TopPicture.mPicBase,
                                                                            BottomPicture.mPicBase);
    return Picture(NewPicture);
}

Picture frame(const Picture &picture) {
    std::shared_ptr<PictureBase> NewPicture = std::make_shared<FramePicture>(picture.mPicBase);
    return Picture(NewPicture);
}

Picture hcat(const Picture &LeftPicture, const Picture &RightPicture) {
    std::shared_ptr<PictureBase> NewPicture = std::make_shared<HCatPicture>(LeftPicture.mPicBase,
                                                                            RightPicture.mPicBase);
    return Picture(NewPicture);
}

