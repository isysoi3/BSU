package controller;

import controller.builder.MedicineBuilder;
import controller.director.MedicineDirector;
import javafx.beans.property.ReadOnlyDoubleWrapper;
import javafx.beans.property.ReadOnlyStringWrapper;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import model.medicine.Medicine;
import model.pharmacy.Pharmacy;
import model.pharmacy.PharmacyManager;

import java.math.BigDecimal;
import java.math.RoundingMode;
import java.text.SimpleDateFormat;

public class Controller {

    /**
     * selected name text field
     */
    @FXML
    public TextField selectNameTextField;

    /**
     * selected min price text field
     */
    @FXML
    public TextField selectMinPriceTextField;
    /**
     * selected max price text field
     */
    @FXML
    public TextField selectMaxPriceTextField;

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


    private Pharmacy pharmacy = new Pharmacy(new PharmacyManager());

    /**
     * initialize some UI method
     */
    @FXML
    private void initialize() {
        addTestData();
        configureTableViewWithColumns();
    }

    /**
     * test medicine data to pharmacy
     */
    private void addTestData() {
        MedicineDirector director = new MedicineDirector();
        MedicineBuilder builder = new MedicineBuilder();
        pharmacy.addMedicine(director.manufactureAntibiotic(builder, "Antibiotic4", 5.5, false));
        builder.reset();

        pharmacy.addMedicine(director.manufactureGell(builder, "gel1", 12.4, true));
        builder.reset();

        pharmacy.addMedicine(director.manufactureGell(builder, "gel2", 32.4, false));
        builder.reset();

        pharmacy.addMedicine(director.manufactureOintment(builder, "Ointment1", 50.5, true));
        builder.reset();

        pharmacy.addMedicine(director.manufactureAntibiotic(builder, "Antibiotic2", 50.5, true));
        builder.reset();
    }

    /**
     * configure table view with columns
     */
    private void configureTableViewWithColumns() {
        SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd");
        nameColumn.setCellValueFactory(cellData -> new ReadOnlyStringWrapper(cellData.getValue().getName()));
        priceColumn.setCellValueFactory(cellData ->
                new ReadOnlyDoubleWrapper(
                        BigDecimal.valueOf(cellData.getValue().getPrice())
                                .setScale(2, RoundingMode.HALF_DOWN)
                                .doubleValue()));
        manufactureDateColumn.setCellValueFactory(cellData -> new ReadOnlyStringWrapper(dateFormat.format(cellData.getValue().getManufactureDate())));
        expirationDateColumn.setCellValueFactory(cellData -> new ReadOnlyStringWrapper(dateFormat.format(cellData.getValue().getExpirationDate())));

        var medicines = pharmacy.getMedicines();
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

    /**
     * handling tap select by name button
     * @param actionEvent some event
     */
    public void onSelectByNameTapped(ActionEvent actionEvent) {
        var name = selectNameTextField.getText();
        if (name.isEmpty()) {
            Alert alert = new Alert(Alert.AlertType.ERROR, "Enter name", ButtonType.OK);
            alert.showAndWait();

            if (alert.getResult() == ButtonType.OK) {
                alert.hide();
            }
        } else {
            tableView.getItems().clear();
            tableView.getItems().addAll(pharmacy.selectMedicinesByName(name));
        }
    }

    /**
     * handling tap drlrvt by price button
     * @param actionEvent some event
     */
    public void onSelectByPriceTapped(ActionEvent actionEvent) {
        var minPrice = selectMinPriceTextField.getText();
        var maxPrice = selectMaxPriceTextField.getText();
        if (maxPrice.isEmpty() || minPrice.isEmpty()) {
            Alert alert = new Alert(Alert.AlertType.ERROR, "Enter price range", ButtonType.OK);
            alert.showAndWait();

            if (alert.getResult() == ButtonType.OK) {
                alert.hide();
            }
        } else {
            System.out.println("Min" + minPrice);
            System.out.println("Max" + maxPrice);

            tableView.getItems().clear();
            tableView.getItems().addAll(pharmacy.selectMedicinesByPriceRange(Double.valueOf(minPrice), Double.valueOf(maxPrice)));
        }
    }

    /**
     * handling tap reset button
     * @param actionEvent some event
     */
    public void onResetButtonTapped(ActionEvent actionEvent) {
        tableView.getItems().clear();
        selectNameTextField.setText(null);
        selectMinPriceTextField.setText(null);
        selectMaxPriceTextField.setText(null);
        tableView.getItems().addAll(pharmacy.getMedicines());
    }
}
