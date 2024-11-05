#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QImage>
#include <QLabel>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QSlider>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

class ImageProcessor : public QMainWindow {
    Q_OBJECT

public:
    ImageProcessor(QWidget *parent = nullptr) : QMainWindow(parent), imageLoaded(false) {
        // Initialize UI components
        QWidget *centralWidget = new QWidget;
        setCentralWidget(centralWidget);
        QVBoxLayout *layout = new QVBoxLayout(centralWidget);

        // Display label for image
        imageLabel = new QLabel("No image loaded", this);
        layout->addWidget(imageLabel);

        // Button for loading an image
        QPushButton *loadButton = new QPushButton("Load Image", this);
        connect(loadButton, &QPushButton::clicked, this, &ImageProcessor::loadImage);
        layout->addWidget(loadButton);

        // Button for saving an image
        QPushButton *saveButton = new QPushButton("Save Image", this);
        connect(saveButton, &QPushButton::clicked, this, &ImageProcessor::saveImage);
        layout->addWidget(saveButton);

        // Button for applying grayscale filter
        QPushButton *grayscaleButton = new QPushButton("Grayscale", this);
        connect(grayscaleButton, &QPushButton::clicked, this, &ImageProcessor::applyGrayscale);
        layout->addWidget(grayscaleButton);

        // Button for applying blur filter
        QPushButton *blurButton = new QPushButton("Blur", this);
        connect(blurButton, &QPushButton::clicked, this, &ImageProcessor::applyBlur);
        layout->addWidget(blurButton);

        // Slider for adjusting brightness
        brightnessSlider = new QSlider(Qt::Horizontal, this);
        brightnessSlider->setRange(-100, 100);
        connect(brightnessSlider, &QSlider::valueChanged, this, &ImageProcessor::adjustBrightness);
        layout->addWidget(brightnessSlider);

        // Set the window size
        resize(800, 600);
    }

public slots:
    void loadImage() {
        QString fileName = QFileDialog::getOpenFileName(this, "Open Image", "", "Images (*.png *.xpm *.jpg)");
        if (!fileName.isEmpty()) {
            image = cv::imread(fileName.toStdString());
            if (!image.empty()) {
                imageLoaded = true;
                displayImage();
            }
        }
    }

    void saveImage() {
        if (imageLoaded) {
            QString fileName = QFileDialog::getSaveFileName(this, "Save Image", "", "Images (*.png *.jpg)");
            if (!fileName.isEmpty()) {
                cv::imwrite(fileName.toStdString(), image);
            }
        }
    }

    void applyGrayscale() {
        if (imageLoaded) {
            cv::cvtColor(image, image, cv::COLOR_BGR2GRAY);
            displayImage();
        }
    }

    void applyBlur() {
        if (imageLoaded) {
            cv::GaussianBlur(image, image, cv::Size(15, 15), 0);
            displayImage();
        }
    }

    void adjustBrightness() {
        if (imageLoaded) {
            int value = brightnessSlider->value();
            cv::Mat tempImage;
            image.convertTo(tempImage, -1, 1, value);  // Increase brightness by `value`
            image = tempImage;
            displayImage();
        }
    }

    void displayImage() {
        if (imageLoaded) {
            cv::cvtColor(image, image, cv::COLOR_BGR2RGB); // Convert BGR to RGB for Qt compatibility
            QImage qImage(image.data, image.cols, image.rows, image.step, QImage::Format_RGB888);
            imageLabel->setPixmap(QPixmap::fromImage(qImage).scaled(image.cols / 2, image.rows / 2, Qt::KeepAspectRatio));
        }
    }

private:
    cv::Mat image;
    bool imageLoaded;
    QLabel *imageLabel;
    QSlider *brightnessSlider;
};

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    ImageProcessor w;
    w.show();

    return a.exec();
}
