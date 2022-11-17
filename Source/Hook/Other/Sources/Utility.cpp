//
// Created by Vojtěch Pröschl on 12.09.2022.
//

#include "../Headers/Utility.hpp"

void copyParmWithInvisible(PRM_Template &source, PRM_Template &destination){
    PRM_Name * newName;

    newName = new PRM_Name(source.getToken(),source.getLabel(),source.getExpressionFlag());
    newName->harden();

    destination.initialize(
            (PRM_Type) (source.getType() | PRM_TYPE_INVISIBLE),
            source.getTypeExtended(),
            source.exportLevel(),
            source.getVectorSize(),
            newName,
            source.getFactoryDefaults(),
            source.getChoiceListPtr(),
            source.getRangePtr(),
            source.getCallback(),
            source.getSparePtr(),
            source.getParmGroup(),
            (const char *)source.getHelpText(),
            source.getConditionalBasePtr()
            );
}

PRM_Template * defaultGeoTemplate() {
    OP_TemplatePair *align, *geo;

    static PRM_Template *theTemplate = 0;

    if(!theTemplate){
        PRM_Template * obj_template;
        int i;
        int size;
        UT_String parm_name;

        obj_template = OBJ_Geometry::getTemplateList(OBJ_PARMS_PLAIN);
        size = PRM_Template::countTemplates( obj_template );
        theTemplate = new PRM_Template[size + 1];   // add +1 for sentinel

        for( i = 0; i < size; i++ ){
            copyParmWithInvisible( obj_template[i], theTemplate[i]);
        }
    }

   return theTemplate;
}
