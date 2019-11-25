#ifndef PROJECT_CHARACTERPICTURES_PICTUREBASE_HPP
#define PROJECT_CHARACTERPICTURES_PICTUREBASE_HPP

#include <string>
#include <vector>
#include <ostream>
#include <memory>

/// Base class for Picture drawing.
class PictureBase {
public:
    typedef size_t size_type;

    /// Virtual destructor
    virtual ~PictureBase() = default;

    virtual size_type getWidth() const = 0;

    virtual size_type getHeight() const = 0;

    /// Displays a row on the given output stream.
    /// \param os An output stream.
    /// \param row Line number to write.
    /// \param pad True if line should have trailing spaces.
    virtual void display(std::ostream &os, size_type row, bool pad) const = 0;

protected:
    /// Pads the line with spaces.
    /// \param ostream Ostream to write to.
    /// \param start Starting index.
    /// \param end One past the end index.
    static void padLine(std::ostream &ostream, size_type start, size_type end);
};

/// Creates a Picture out of an array of strings.
class StringPicture : public PictureBase {
public:
    /// Creates a picture from a list of lines. Makes the most basic picture.
    /// \param lines Vector of lines to use.
    explicit StringPicture(std::vector<std::string> lines);

    size_type getWidth() const override;

    size_type getHeight() const override;

    void display(std::ostream &os, size_type row, bool pad) const override;

private:
    // Data
    std::vector<std::string> mData;
};

/// Frames a Picture by the amount of spaces and using a given frame character.
class FramePicture : public PictureBase {
public:
    /// Frames a given picture using the frame character and leaving space as margins.
    /// \param picture Picture to frame.
    /// \param spaces Amount of spaces to use as margin.
    /// \param frame Character to frame the picture with.
    explicit FramePicture(std::shared_ptr<PictureBase> picture, int spaces = 1, char frame = '*');

    size_type getWidth() const override;

    size_type getHeight() const override;

    void display(std::ostream &os, size_type row, bool pad) const override;

private:
    // Picture
    std::shared_ptr<PictureBase> mPicture;
    int mSpaces;
    char mFrame;
};

/// Allows the concatenation of two Pictures vertically.
class VCatPicture : public PictureBase {
public:
    /// Vertically concatenates two pictures.
    /// \param upper Upper picture.
    /// \param lower Lower picture.
    VCatPicture(std::shared_ptr<PictureBase> upper, std::shared_ptr<PictureBase> lower);

    size_type getWidth() const override;

    size_type getHeight() const override;

    void display(std::ostream &os, size_type row, bool pad) const override;

private:
    // Other pictures
    std::shared_ptr<PictureBase> mUpper, mLower;
};

/// Allows the concatenation of two Pictures horizontally.
class HCatPicture : public PictureBase {
public:
    /// Horizontally concatenates two pictures.
    /// \param left Left picture.
    /// \param right Right picture.
    HCatPicture(std::shared_ptr<PictureBase> left, std::shared_ptr<PictureBase> right);

    size_type getWidth() const override;

    size_type getHeight() const override;

    void display(std::ostream &os, size_type row, bool pad) const override;

private:
    // Other pictures
    std::shared_ptr<PictureBase> mLeft, mRight;
};


#endif //PROJECT_CHARACTERPICTURES_PICTUREBASE_HPP
