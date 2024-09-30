TARGET     = $$qtLibraryTarget(pluginloader)  # Nom del plugin 

include(../common.pro)
QMAKE_CXXFLAGS += -DGRACETIME=2500
