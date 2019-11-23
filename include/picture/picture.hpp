#ifndef PROJECT_CHARACTERPICTURES_PICTURE_HPP
#define PROJECT_CHARACTERPICTURES_PICTURE_HPP

#include <picture/pic_base.hpp>
#include <string>
#include <vector>
#include <ostream>
#include <memory>

/**
 * User class to represent different pictures.
 */
class Picture {
public:
    /**
     * Default constructor
     * @param lines Initial lines for the picture.
     */
    Picture(const std::vector<std::string> &lines = std::vector<std::string>());

    /**
     * Constructor from initializer list
     * @param lines
     */
    Picture(std::initializer_list<std::string> lines);

    /**
     * Constructor from a PicBase.
     * @param picBase
     */
    Picture(std::shared_ptr<PicBase> picBase);

private:
    // Internal data
    std::shared_ptr<PicBase> mPicBase;

    // Friend declarations
    friend Picture frame(const Picture &picture);
    friend Picture hcat(const Picture &left_picture, const Picture &right_picture);
    friend Picture vcat(const Picture &top_picture, const Picture &bottom_picture);
    friend std::ostream &operator<<(std::ostream &os, const Picture &picture);
};

/**
 * Constructs a framed picture out of a picture.
 * @param picture Picture to frame.
 * @return
 */
Picture frame(const Picture &picture);

/**
 * Horizontally concatenates two pictures together.
 * @param left_picture
 * @param right_picture
 * @return
 */
Picture hcat(const Picture &left_picture, const Picture &right_picture);

/**
 * Vertically concatenates two pictures together.
 * @param top_picture
 * @param bottom_picture
 * @return
 */
Picture vcat(const Picture &top_picture, const Picture &bottom_picture);

/**
 * Writes the contents of a Picture to the provided ostream.
 * @param os
 * @param picture
 * @return
 */
std::ostream &operator<<(std::ostream &os, const Picture &picture);


#endif //PROJECT_CHARACTERPICTURES_PICTURE_HPP
