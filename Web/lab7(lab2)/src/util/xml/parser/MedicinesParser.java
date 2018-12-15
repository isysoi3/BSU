package util.xml.parser;

import exception.ParserException;
import model.medicine.Medicine;
import java.util.List;

public interface MedicinesParser {
    List<Medicine> parse(String fileName) throws ParserException;
}
