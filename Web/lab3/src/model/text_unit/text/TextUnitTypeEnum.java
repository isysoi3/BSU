package model.text_unit.text;

public enum TextUnitTypeEnum {
    WORD {
        @Override
        public String toString() {
            return "word";
        }
    },
    PUNCTUATION_MARK {
        @Override
        public String toString() {
            return "punctuation mark";
        }
    },
    CODE_LEXEME {
        @Override
        public String toString() {
            return "code lexeme";
        }
    },
    SENTENCE {
        @Override
        public String toString() {
            return "sentence";
        }
    },
    CODE_LINE {
        @Override
        public String toString() {
            return "code line";
        }
    },
    PARAGRAPH {
        @Override
        public String toString() {
            return "paragraph";
        }
    },
    CODE {
        @Override
        public String toString() {
            return "code";
        }
    },
    TEXT {
        @Override
        public String toString() {
            return "text";
        }
    }

}
