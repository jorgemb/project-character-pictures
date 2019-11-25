#ifndef PROJECT_CHARACTERPICTURES_PICTURE_HPP
#define PROJECT_CHARACTERPICTURES_PICTURE_HPP

#include <picture/PictureBase.hpp>
#include <string>
#include <vector>
#include <ostream>
#include <memory>

/// User class to represent different pictures.
class Picture {
public:
    /// Constructs a basic Picture based on string lines.
    /// \param lines Initial lines for the Picture.
    Picture(const std::vector<std::string> &lines = std::vector<std::string>());

    /// Constructs a basic Picture based on string lines.
    /// \param lines Initial lines for the Picture.
    Picture(std::initializer_list<std::string> lines);

    /// Constructor from a PictureBase.
    /// \param picBase Picture base
    Picture(std::shared_ptr<PictureBase> picBase);

private:
    /// Internal PictureBase
    std::shared_ptr<PictureBase> mPicBase;

    // Friend declarations
    friend Picture frame(const Picture &picture);

    friend Picture hcat(const Picture &LeftPicture, const Picture &RightPicture);

    friend Picture vcat(const Picture &TopPicture, const Picture &BottomPicture);

    friend std::ostream &operator<<(std::ostream &os, const Picture &picture);
};

/// Constructs a framed picture out of a picture.
/// \param picture Picture to frame.
/// \return
Picture frame(const Picture &picture);

/// Horizontally concatenates two pictures together.
/// \param LeftPicture
/// \param RightPicture
/// \return
Picture hcat(const Picture &LeftPicture, const Picture &RightPicture);

/// Vertically concatenates two pictures together.
/// \param TopPicture
/// \param BottomPicture
/// \return
Picture vcat(const Picture &TopPicture, const Picture &BottomPicture);

/// Writes the contents of a Picture to the provided ostream.
/// \param os
/// \param picture
/// \return
std::ostream &operator<<(std::ostream &os, const Picture &picture);


#endif //PROJECT_CHARACTERPICTURES_PICTURE_HPP
