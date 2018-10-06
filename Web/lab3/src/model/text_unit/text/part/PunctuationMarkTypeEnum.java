package model.text_unit.text.part;

public enum PunctuationMarkTypeEnum {
    DOT {
        @Override
        public String toString() {
            return ".";
        }
    },
    COMMA {
        @Override
        public String toString() {
            return ",";
        }
    },
    EXCLAMATION {
        @Override
        public String toString() {
            return "!";
        }
    },
    QUESTION {
        @Override
        public String toString() {
            return "?";
        }
    },
    COLON {
        @Override
        public String toString() {
            return ":";
        }
    },
    SEMICOLON {
        @Override
        public String toString() {
            return ";";
        }
    },
    SINGLE_QUOTES {
        @Override
        public String toString() {
            return "'";
        }
    },
    QUOTES {
        @Override
        public String toString() {
            return "\"";
        }
    }
}
