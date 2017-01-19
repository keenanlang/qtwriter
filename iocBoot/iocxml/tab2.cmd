UIStartObject("TEST", "widget", "class=QWidget, name=layoutWidget2")
UISetProperty("TEST", "name=geometry", "rect", "", "x=20, y=20, width=330, height=330")
UISetLayout("TEST", "QHBoxLayout", "horizontalLayout")

UIStartObject("TEST", "widget", "class=caLinearGauge, name=gauge1")
UIEndObject("TEST")

UIStartObject("TEST", "spacer", "name=verticalSpacer")
UISetProperty("TEST", "name=orientation", "enum", "Qt::Vertical", "")
UIEndObject("TEST")

UIStartObject("TEST", "widget", "class=caLinearGauge, name=gauge2")
UIEndObject("TEST")

UIEndObject("TEST")
