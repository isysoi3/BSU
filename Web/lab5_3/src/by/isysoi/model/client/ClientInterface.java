package by.isysoi.model.client;

import javax.swing.*;
import java.util.List;

public interface ClientInterface {

    String getName();

    String getAnotherClientName();

    JFrame getFrame();

    JList<ImageIcon> getImageList();

    List<ImageIcon> getMyImages();

}
