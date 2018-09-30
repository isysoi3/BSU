package controller;

import javafx.beans.property.ReadOnlyDoubleWrapper;
import javafx.beans.property.ReadOnlyStringWrapper;
import javafx.fxml.FXML;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TablePosition;
import javafx.scene.control.TableView;
import javafx.scene.control.TextArea;
import model.medicine.Medicine;
import model.pharmacy.*;
import model.pharmacy.PharmacyManager;

import java.math.BigDecimal;
import java.math.RoundingMode;
import java.text.SimpleDateFormat;

public class Controller {

    /**
     * table view of medicines
     */
    @FXML
    private TableView<Medicine> tableView = new TableView<>();

    /**
     * column of medicine name
     */
    @FXML
    private TableColumn<Medicine, String> nameColumn = new TableColumn<>();

    /**
     * column of medicine price
     */
    @FXML
    private TableColumn<Medicine, Number> priceColumn = new TableColumn<>();

    /**
     * column of medicine manufacture date
     */
    @FXML
    private TableColumn<Medicine, String> manufactureDateColumn = new TableColumn<>();

    /**
     * column of medicine expiration date
     */
    @FXML
    private TableColumn<Medicine, String> expirationDateColumn = new TableColumn<>();

    /**
     * text area to show some info
     */
    @FXML
    private TextArea medicineDescriptionTextArea;


    /**
     * initialize some UI method
     */
    @FXML
    private void initialize() {
        SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd");
        nameColumn.setCellValueFactory(cellData -> new ReadOnlyStringWrapper(cellData.getValue().getName()));
        priceColumn.setCellValueFactory(cellData ->
                new ReadOnlyDoubleWrapper(BigDecimal.valueOf(cellData.getValue().getPrice())
                        .setScale(3, RoundingMode.HALF_UP)
                        .doubleValue()));
        manufactureDateColumn.setCellValueFactory(cellData -> new ReadOnlyStringWrapper(dateFormat.format(cellData.getValue().getManufactureDate())));
        expirationDateColumn.setCellValueFactory(cellData -> new ReadOnlyStringWrapper(dateFormat.format(cellData.getValue().getExpirationDate())));

        var medicines = (new PharmacyController(new Pharmacy(new PharmacyManager()))).getPharmacyMedicines();
        tableView.getItems().addAll(medicines);

        tableView.setEditable(false);
        tableView.setOnMouseClicked(click -> {
            if (click == null)
                return;
            if (click.getClickCount() == 1) {
                medicineDescriptionTextArea.setText(tableView.getSelectionModel().getSelectedItem().toString());
            }
        });
    }


}
