package view;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;


/**
 * class to run JavaFX app
 *
 * @author Ilya Sysoi
 * @version 1.0.0
 */
public class Main extends Application {

    @Override
    public void start(Stage primaryStage) throws Exception {
        Parent root = FXMLLoader.load(getClass().getResource("sample.fxml"));
        primaryStage.setTitle("Pharmacy MINSK 2.0");
        primaryStage.setResizable(false);
        primaryStage.setScene(new Scene(root, 780, 500));
        primaryStage.show();
    }

    /**
     * start method
     * @param args args of app
     */
    public static void main(String[] args) {
        launch(args);
    }
}
