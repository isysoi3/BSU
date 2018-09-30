package controller;

import javafx.beans.property.ReadOnlyDoubleProperty;
import javafx.beans.property.ReadOnlyDoubleWrapper;
import javafx.beans.property.ReadOnlyProperty;
import javafx.beans.property.ReadOnlyStringWrapper;
import javafx.fxml.FXML;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.TextArea;
import model.medicine.Medicine;
import model.pharmacy.Pharmacy;
import model.pharmacy.PharmacyManager;

import javax.xml.crypto.Data;
import java.math.BigDecimal;
import java.math.RoundingMode;
import java.text.SimpleDateFormat;

public class Controller {

    @FXML
    private TableView<Medicine> tableView = new TableView<>();

    @FXML
    private TableColumn<Medicine, String> nameColumn = new TableColumn<>();

    @FXML
    private TableColumn<Medicine, Number> priceColumn = new TableColumn<>();

    @FXML
    private TableColumn<Medicine, String> manufactureDateColumn = new TableColumn<>();

    @FXML
    private TableColumn<Medicine, String> expirationDateColumn = new TableColumn<>();

    @FXML
    private TextArea medicineDescriptionTextArea;


    @FXML
    private void initialize() {
        SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd");
        nameColumn.setCellValueFactory(cellData -> new ReadOnlyStringWrapper(cellData.getValue().getName()));
        priceColumn.setCellValueFactory(cellData ->
                new ReadOnlyDoubleWrapper(BigDecimal.valueOf(cellData.getValue().getPrice())
                        .setScale(3, RoundingMode.HALF_UP)
                        .doubleValue()));
        manufactureDateColumn.setCellValueFactory(cellData -> new ReadOnlyStringWrapper(dateFormat.format(cellData.getValue().getManufactureDate())));
        expirationDateColumn.setCellValueFactory(cellData ->  new ReadOnlyStringWrapper(dateFormat.format(cellData.getValue().getExpirationDate())));

        var medicines = (new PharmacyController(new Pharmacy(new PharmacyManager()))).getPharmacyMedicines();
        tableView.getItems().addAll(medicines);
    }


}
