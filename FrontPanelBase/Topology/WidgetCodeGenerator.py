import json

class WidgetCodeGenerator:
    def __init__(self, filename):
        with open(filename) as f:
            self.topology = json.load(f)
            baseName = os.path.basename(filename)
            self.fileNameWoExt = os.path.splitext(baseName)[0]

    def createCppTopologyHeader(self):
        strOutFile = self.fileNameWoExt + ".h"
        with open(strOutFile, "w") as outFile:
            outFile.write(self._createCppTopologyHeader(strOutFile))

    def _createCppTopologyHeader(self, outFile):
        ret = "/* GENERATED HEADER, Don't modify!!! */\n"
        includeGuard = str(outFile).upper().replace(".", "_") 
        ret += "#ifndef " + includeGuard + "\n"
        ret += "#define " + includeGuard + "\n\n"
        ret += "#include \"FpVector2D.h\"\n"
        ret += "#include \"FpGfxTypes.h\"\n"
        ret += "#include \"FpButton.h\"\n"
        ret += "#include \"FpButton3d.h\"\n"
        ret += "#include \"FpButton5d.h\"\n"
        ret += "#include \"FpEncoder.h\"\n"
        ret += "#include \"FpPotentiometer.h\"\n"
        ret += "#include \"FpTouchSurface.h\"\n"
        ret += "#include <cstdint>\n"
        ret += "#include <string>\n\n"
        ret += "namespace fp\n"
        ret += "{\n\n"
        ret += "struct " + self.fileNameWoExt + "\n"
        ret += "{\n"
        for widgetType in self.topology.keys():
            ret += "struct " + widgetType + "\n{\n"
            # ------- Enumeration ----------
            ret += "   enum Id\n"
            ret += "   {\n"
            widgetId = 0
            lastLabel = None
            for label in self.topology[widgetType].keys():
                ret += "      e" + label + " = " + str(widgetId) + ",\n"
                widgetId += 1
                lastLabel = "e" + label
            if lastLabel:
                ret += "      eLast = " + lastLabel + "\n"
            else:
                ret += "      eLast = -1\n"
            ret += "   };\n\n"
            # ------- To String conversion ----------
            ret += "   static std::string id2Str(Id widgetId)\n"
            ret += "   {\n"
            ret += "        switch(widgetId)\n"
            ret += "        {\n"
            for label in self.topology[widgetType].keys():
                ret += "            case e" + label + ": return " + "\"" + label + "\";\n" 
            ret += "            default: return std::string();\n"
            ret += "        }\n"
            ret += "   }\n\n"
            # ------- Link to Widget Type ----------
            if widgetType != "Led" and widgetType != "Positioner" and widgetType != "Display":
                ret += "   using WidgetType = fp::" + widgetType + ";\n\n"
            # ------- Getting Dimension ----------
            ret += "   static constexpr Vector2d<uint8_t> getDim(Id widgetId) noexcept\n"
            ret += "   {\n"
            dimStr = ""
            for label in self.topology[widgetType].keys():
                widget = self.topology[widgetType][label]
                if dimStr:
                    dimStr += ", "
                i = str(widget['Dimension'][0])
                j = str(widget['Dimension'][1])
                dimStr += "{" + i + ", " + j + "}"
            if dimStr:
                ret += "      constexpr Vector2d<uint8_t> dim[Id::eLast + 1] = { " + dimStr + "} ;\n"
                ret += "      return dim[widgetId];\n"
            else:
                ret += "      constexpr Vector2d<uint8_t> dim = {0,0};\n"
                ret += "      return dim;\n"
            ret += "   }\n\n"
            # ------- Getting Resolution ----------
            if widgetType == "Potentiometer" or\
               widgetType == "Positioner" :
                resolutionStr = ""
                ret += "   static uint32_t getResolution(Id widgetId)\n"
                ret += "   {\n"
                for label in self.topology[widgetType].keys():
                    widget = self.topology[widgetType][label]
                    if resolutionStr:
                        resolutionStr += ", "
                    resolutionStr += str(widget['Resolution'])
                if resolutionStr:
                    ret += "      const uint32_t res[Id::eLast + 1] = { " + resolutionStr + "} ;\n"
                    ret += "      return res[widgetId];\n"
                else:
                    ret += "      const uint32_t res = 0;\n"
                    ret += "      return res;\n"
                ret += "   }\n"

            elif widgetType == "Display":
                resolutionStr = ""
                ret += "   static const gfx::Resolution &getResolution(Id widgetId)\n"
                ret += "   {\n"
                for label in self.topology[widgetType].keys():
                    widget = self.topology[widgetType][label]
                    if resolutionStr:
                        resolutionStr += ", "
                    resXStr = str(widget['Resolution'][0])
                    resYStr = str(widget['Resolution'][1])
                    resolutionStr += "{ " + resXStr + ", " + resYStr + " }"
                if resolutionStr:
                    ret += "      static const Vector2d<uint32_t> res[Id::eLast + 1] = { " + resolutionStr + "} ;\n"
                    ret += "      return res[widgetId];\n"
                else:
                    ret += "      static const Vector2d<uint32_t> res = {0,0};\n"
                    ret += "      return res;\n"
                ret += "   }\n"

            elif widgetType == "TouchSurface":
                resolutionStr = ""
                ret += "   static const gfx::Resolution &getResolution(Id widgetId)\n"
                ret += "   {\n"
                for label in self.topology[widgetType].keys():
                    widget = self.topology[widgetType][label]
                    if resolutionStr:
                        resolutionStr += ", "
                    resXStr = str(widget['Resolution'][0])
                    resYStr = str(widget['Resolution'][1])
                    resolutionStr += "{ " + resXStr + ", " + resYStr + " }"
                if resolutionStr:
                    ret += "      static const Vector2d<uint32_t> res[Id::eLast + 1] = { " + resolutionStr + "} ;\n"
                    ret += "      return res[widgetId];\n"
                else:
                    ret += "      static const Vector2d<uint32_t> res = {0,0};\n"
                    ret += "      return res;\n"
                ret += "   }\n"

            elif widgetType == "Button3d":
                resolutionStr = ""
                ret += "   static uint32_t getVelocityResolution(Id widgetId)\n"
                ret += "   {\n"
                for label in self.topology[widgetType].keys():
                    widget = self.topology[widgetType][label]
                    if resolutionStr:
                        resolutionStr += ", "
                    resolutionStr += str(widget['Resolution']['Velocity']) 
                if resolutionStr:
                    ret += "      const uint32_t res[Id::eLast + 1] = { " + resolutionStr + "} ;\n"
                    ret += "      return res[widgetId];\n"
                else:
                    ret += "      const uint32_t res = 0;\n"
                    ret += "      return res;\n"
                ret += "   }\n\n"
                resolutionStr = ""
                ret += "   static uint32_t getPressureResolution(Id widgetId)\n"
                ret += "   {\n"
                for label in self.topology[widgetType].keys():
                    widget = self.topology[widgetType][label]
                    if resolutionStr:
                        resolutionStr += ", "
                    resolutionStr += str(widget['Resolution']['Pressure'])
                if resolutionStr:
                    ret += "      const uint32_t res[Id::eLast + 1] = { " + resolutionStr + "} ;\n"
                    ret += "      return res[widgetId];\n"
                else:
                    ret += "      const uint32_t res = 0;\n"
                    ret += "      return res;\n"
                ret += "   }\n\n"

            elif widgetType == "Button5d":
                resolutionStr = ""
                ret += "   static uint32_t getVelocityResolution(Id widgetId)\n"
                ret += "   {\n"
                for label in self.topology[widgetType].keys():
                    widget = self.topology[widgetType][label]
                    if resolutionStr:
                        resolutionStr += ", "
                    resolutionStr += str(widget['Resolution']['Velocity']) 
                if resolutionStr:
                    ret += "      const uint32_t res[Id::eLast + 1] = { " + resolutionStr + "} ;\n"
                    ret += "      return res[widgetId];\n"
                else:
                    ret += "      const uint32_t res = 0;\n"
                    ret += "      return res;\n"
                ret += "   }\n\n"
                resolutionStr = ""
                ret += "   static uint32_t getPressureResolution(Id widgetId)\n"
                ret += "   {\n"
                for label in self.topology[widgetType].keys():
                    widget = self.topology[widgetType][label]
                    if resolutionStr:
                        resolutionStr += ", "
                    resolutionStr += str(widget['Resolution']['Pressure'][2])
                if resolutionStr:
                    ret += "      const uint32_t res[Id::eLast + 1] = { " + resolutionStr + "} ;\n"
                    ret += "      return res[widgetId];\n"
                else:
                    ret += "      const uint32_t res = 0;\n"
                    ret += "      return res;\n"
                ret += "   }\n\n"
                resolutionStr = ""
                ret += "   static const Vector2d<uint32_t> &getSurfaceResolution(Id widgetId)\n"
                ret += "   {\n"
                for label in self.topology[widgetType].keys():
                    widget = self.topology[widgetType][label]
                    if resolutionStr:
                        resolutionStr += ", "
                    resXStr = str(widget['Resolution']['Pressure'][0])
                    resYStr = str(widget['Resolution']['Pressure'][1])
                    resolutionStr += "{ " + resXStr + ", " + resYStr + " }"
                if resolutionStr:
                    ret += "      static const Vector2d<uint32_t> res[Id::eLast + 1] = { " + resolutionStr + "} ;\n"
                    ret += "      return res[widgetId];\n"
                else:
                    ret += "      static const Vector2d<uint32_t> res = {0,0};\n"
                    ret += "      return res;\n"
                ret += "   }\n"

            ret += "};\n\n"
        ret += "}; // struct " + self.fileNameWoExt + "\n"
        ret += "} // namespace fp\n"
        ret += "#endif"

        return ret

if __name__ == "__main__":
    import sys
    import os.path
    if len(sys.argv) < 2:
        print("Filename needed as an argument\n")
        exit(1)
    jsonName = sys.argv[1]
    topology = WidgetCodeGenerator(str(jsonName))
    baseName = os.path.basename(jsonName)
    woExt = os.path.splitext(baseName)[0]
    topology.createCppTopologyHeader()
