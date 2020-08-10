DSPBASE = DSP

DSPSRC = 

# Required include directories
DSPINC += inc

#include $(DSPBASE)/BasicMathFunctions/files.mk
#include $(DSPBASE)/CommonTables/files.mk
#include $(DSPBASE)/ComplexMathFunctions/files.mk
#include $(DSPBASE)/ControllerFunctions/files.mk
#include $(DSPBASE)/FastMathFunctions/files.mk
include $(DSPBASE)/FilteringFunctions/files.mk
#include $(DSPBASE)/MatrixFunctions/files.mk
#include $(DSPBASE)/StatisticsFunctions/files.mk
#include $(DSPBASE)/SupportFunctions/files.mk
#include $(DSPBASE)/TransformFunctions/files.mk