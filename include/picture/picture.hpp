#ifndef PROJECT_CHARACTERPICTURES_PICTURE_HPP
#define PROJECT_CHARACTERPICTURES_PICTURE_HPP

#include <string>
#include <vector>
#include <ostream>
#include <memory>


class PicBase {
public:
    typedef std::size_t size_type;

    /**
     * Virtual destructor.
     */
    virtual ~PicBase() {}

    /**
     * @return The width of the Picture.
     */
    virtual size_type width() const = 0;

    /**
     * @return The height of the Picture.
     */
    virtual size_type height() const = 0;

    /**
     * Displays a row on the given output stream.
     * @param os Output stream.
     * @param row Line to write.
     * @param pad Pad the line with trailing spaces.
     */
    virtual void display(std::ostream &os, size_type row, bool pad) const = 0;

protected:
    /**
     * Pads the line with spaces.
     * @param ostream
     * @param start
     * @param end
     */
    static void pad_line(std::ostream &ostream, size_type start, size_type end);
};


class StringPicture : public PicBase {
public:
    /**
     * Constructor from a series of strings.
     * @param lines
     */
    StringPicture(std::vector<std::string> lines);

    size_type width() const override;

    size_type height() const override;

    void display(std::ostream &os, size_type row, bool pad) const override;

private:
    // Data
    std::vector<std::string> mData;
};

class FramePicture : public PicBase {
public:
    /**
     * Constructor from picture.
     */
    FramePicture(std::shared_ptr<PicBase> picture, int spaces = 1, char frame = '*');

    size_type width() const override;

    size_type height() const override;

    void display(std::ostream &os, size_type row, bool pad) const override;

private:
    // Picture
    std::shared_ptr<PicBase> mPicture;
    int mSpaces;
    char mFrame;
};

class VCatPicture : public PicBase {
public:
    /**
     * Constructor with upper and lower.
     * @param upper
     * @param lower
     */
    VCatPicture(std::shared_ptr<PicBase> upper, std::shared_ptr<PicBase> lower);

    size_type width() const override;

    size_type height() const override;

    void display(std::ostream &os, size_type row, bool pad) const override;

private:
    // Other pictures
    std::shared_ptr<PicBase> mUpper, mLower;
};

class HCatPicture : public PicBase {
public:
    /**
     * Constructor with left and right.
     */
    HCatPicture(std::shared_ptr<PicBase> left, std::shared_ptr<PicBase> right);

    size_type width() const override;

    size_type height() const override;

    void display(std::ostream &os, size_type row, bool pad) const override;

private:
    // Other pictures
    std::shared_ptr<PicBase> mLeft, mRight;
};

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

Picture frame(const Picture &picture);

Picture hcat(const Picture &left_picture, const Picture &right_picture);

Picture vcat(const Picture &top_picture, const Picture &bottom_picture);

std::ostream &operator<<(std::ostream &os, const Picture &picture);


#endif //PROJECT_CHARACTERPICTURES_PICTURE_HPP
