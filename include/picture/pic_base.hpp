#ifndef PROJECT_CHARACTERPICTURES_PIC_BASE_HPP
#define PROJECT_CHARACTERPICTURES_PIC_BASE_HPP

#include <string>
#include <vector>
#include <ostream>
#include <memory>

/**
 * Base class for Picture drawing.
 */
class PicBase {
public:
    typedef size_t size_type;

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

/**
 * Creates a Picture out of an array of strings.
 */
class StringPicture : public PicBase {
public:
    StringPicture(std::vector<std::string> lines);
    size_type width() const override;
    size_type height() const override;
    void display(std::ostream &os, size_type row, bool pad) const override;
private:
    // Data
    std::vector<std::string> mData;
};

/**
 * Frames a Picture by the amount of spaces and using a given frame character.
 */
class FramePicture : public PicBase {
public:
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

/**
 * Vertically concatenates two pictures.
 */
class VCatPicture : public PicBase {
public:
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


#endif //PROJECT_CHARACTERPICTURES_PIC_BASE_HPP
