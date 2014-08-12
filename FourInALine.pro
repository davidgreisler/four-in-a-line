TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS = src/src.pro \
          app/FourInALine.pro \
          app/app.pro \
          tests/Game/BoardTest.pro \
          tests/Game/CellSetTest.pro \
          tests/Game/CellSetIteratorTest.pro \
          tests/Game/FourInALine/ArtificialIntelligenceTest.pro \
          tests/Game/FourInALine/AsynchronousArtificialIntelligenceTest.pro \
          tests/Game/FourInALine/BoardTest.pro \
          tests/Game/FourInALine/GameTest.pro \
          tests/GUI/BoardTest.pro

TRANSLATIONS = resources/i18n/fourinaline_en.ts \
               resources/i18n/fourinaline_de.ts

# Documentation

doc.depends = doc_run_doxygen
doc.target = doc

doc_run_doxygen.commands = doxygen

QMAKE_EXTRA_TARGETS += doc doc_run_doxygen

