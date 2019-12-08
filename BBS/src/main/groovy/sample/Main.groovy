package sample

import javafx.application.Application
import javafx.fxml.FXMLLoader
import javafx.scene.Parent
import javafx.scene.Scene
import javafx.stage.Stage

class Main extends Application
{
    @Override
    void start(Stage primaryStage) throws Exception {
        Parent root = FXMLLoader.load(getClass().getResource("/fxml/sample.fxml"))
        primaryStage.setTitle("BBS")
        primaryStage.setScene(new Scene(root, 700, 400))
        primaryStage.show()
    }

    static void main(String[] args) {
        launch(Main, args)
    }
}
