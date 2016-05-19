import javax.imageio.ImageIO;
import java.awt.*;
import java.awt.color.ColorSpace;
import java.awt.image.*;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Main {

    private static ExecutorService tpool = Executors.newFixedThreadPool(1000);

    public static void main(String[] args) throws IOException {
        resize();
    }

    private static void resize() throws IOException {
        File imgPath = new File("/home/dsp/Desktop/1.jpg");
        BufferedImage bufferedImage = ImageIO.read(imgPath);
        System.out.println(bufferedImage.getWidth() + "*" + bufferedImage.getHeight());

        WritableRaster raster = bufferedImage.getRaster();
        DataBufferByte data = (DataBufferByte) raster.getDataBuffer();

        byte[] bytes = data.getData();
        final byte[][] rgbs = new byte[bytes.length / 3][3];

        int count = 0;
        for (int i = 0; i < bytes.length; i += 3) {
            rgbs[count][0] = bytes[i];
            rgbs[count][1] = bytes[i + 1];
            rgbs[count][2] = bytes[i + 2];
            count++;
        }
        final int width = bufferedImage.getWidth();
        int height = bufferedImage.getHeight();
        final ArrayList<byte[]> rgbsTemp = new ArrayList<>();

        for (int j = 0; j < height; j += 2) {
            for (int i = j * width; i < (j * width) + (width); i += 2) {
                rgbsTemp.add(getAverageRGB(rgbs[i], rgbs[i + 1], rgbs[width + i], rgbs[i + width + 1]));
                final int finalI = i;
                Thread thread = new Thread(new Runnable() {
                    @Override
                    public void run() {
                        rgbsTemp.add(getAverageRGB(rgbs[finalI], rgbs[finalI + 1], rgbs[width + finalI], rgbs[finalI + width + 1]));
                    }
                });
                tpool.execute(thread);
            }
        }
        tpool.shutdown();
        byte[] finalBytes = new byte[width * height * 3 / 4];
        count = 0;
        for (int i = 0; i < rgbsTemp.size(); i++) {
            for (int j = 0; j < 3; j++) {
                finalBytes[count] = rgbsTemp.get(i)[j];
                count++;
            }
        }
        File f = new File("/home/dsp/Desktop/1-resized.png");
        ImageIO.write(createRGBImage(finalBytes, width / 2, height / 2), "PNG", f);

    }

    public static byte[] getAverageRGB(byte[] rgb, byte[] rgb1, byte[] rgb2, byte[] rgb3) {
        byte[] averageRGB = new byte[3];
        for (int i = 0; i < 3; i++) {
            int sum = ((int) rgb[i] + (int) rgb1[i] + (int) rgb2[i] + (int) rgb3[i]) / 4;
            averageRGB[i] = (byte) sum;
        }
        return averageRGB;
    }

    private static BufferedImage createRGBImage(byte[] bytes, int width, int height) {
        DataBufferByte buffer = new DataBufferByte(bytes, bytes.length);
        ColorModel cm = new ComponentColorModel(ColorSpace.getInstance(ColorSpace.CS_sRGB), new int[]{8, 8, 8}, false, false, Transparency.OPAQUE, DataBuffer.TYPE_BYTE);
        return new BufferedImage(cm, Raster.createInterleavedRaster(buffer, width, height, width * 3, 3, new int[]{0, 1, 2}, null), false, null);
    }
}
