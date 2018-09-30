package controller;

import javafx.beans.property.ReadOnlyStringWrapper;
import javafx.fxml.FXML;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.TextArea;
import model.medicine.Medicine;
import model.pharmacy.Pharmacy;
import model.pharmacy.PharmacyManager;

public class Controller {

    @FXML
    private TableView<Medicine> tableView = new TableView<>();

    @FXML
    private TableColumn<Medicine, String> nameColumn = new TableColumn<>();

    @FXML
    private TableColumn<Medicine, String> priceColumn = new TableColumn<>();

    @FXML
    private TableColumn<Medicine, String> manufactureDateColumn = new TableColumn<>();

    @FXML
    private TableColumn<Medicine, String> expirationDateColumn = new TableColumn<>();

    @FXML
    private TextArea medicineDescriptionTextArea;


    @FXML
    private void initialize() {
        nameColumn.setCellValueFactory(cellData -> new ReadOnlyStringWrapper(cellData.getValue().getName()));
        priceColumn.setCellValueFactory(cellData -> new ReadOnlyStringWrapper(String.valueOf(cellData.getValue().getPrice())));
        manufactureDateColumn.setCellValueFactory(cellData -> new ReadOnlyStringWrapper(cellData.getValue().getManufactureDate().toString()));
        expirationDateColumn.setCellValueFactory(cellData ->  new ReadOnlyStringWrapper(cellData.getValue().getExpirationDate().toString()));


        var medicines = (new PharmacyController(new Pharmacy(new PharmacyManager()))).getPharmacyMedicines();
        tableView.getItems().addAll(medicines);

    }


}
