/*
	Phrase.cpp
 
	Code for the OrangeLine module Phrase

Copyright (C) 2019 Dieter Stubler

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#include <string>
#include <stdio.h>
#include <limits.h>

#include "Phrase.hpp"

struct Phrase : Module {

	#include "OrangeLineCommon.hpp"

	// ********************************************************************************************************************************
	/*
		Module member variables
	*/
	int   phraseDurCounter   = 0;
	int   phraseLenCounter   = 0;
	int   slaveLenCounter    = 0;
	int   masterDelayCounter = 0;
	int   clockDelayCounter  = 0;
	bool  clockWithReset     = false;
	bool  clockWithSpa       = false;
	bool  clockWithSph       = false;
	float slavePattern       = 0;
	int   divCounter         = 0;
	float defaultPhraseLen ;
	float oldClkInputVoltage = 0;
	int   oldClockDelayCounter = 0;
	int   oldMasterDelayCounter = 0;


// ********************************************************************************************************************************
/*
	Initialization
*/
	/**
		Constructor

		Typically just calls initializeInstance included from OrangeLineCommon.hpp
	*/
	Phrase () {
		initializeInstance ();
	}
	/*
		Method to decide whether this call of process() should be skipped

		Only process when idleSkipCOunter provided by OrangeLineCommmon.hpp == 0
		or we are running some delayed processing
		or if we have a clock trigger.
		We must not do a trigger process here but just check if the clock trigger input changed
	*/
	bool moduleSkipProcess() {
		bool skip = (idleSkipCounter != 0);
		float clkInputVolgate = inputs[CLK_INPUT].getVoltage (); 
		if (clkInputVolgate    != oldClkInputVoltage ||
			clockDelayCounter  != oldClockDelayCounter ||
			masterDelayCounter != oldMasterDelayCounter
		   ) {
			skip = false;
		}
		oldClockDelayCounter  = clockDelayCounter;
		oldMasterDelayCounter = masterDelayCounter;
		oldClkInputVoltage    = clkInputVolgate;
		return skip;
	}
	/**
		Method to set stateTypes != default types set by initializeInstance() in OrangeLineModule.hpp
		which is called from constructor
	*/
	void moduleInitStateTypes () {
		setStateTypeInput        (RST_INPUT, STATE_TYPE_TRIGGER);
		setStateTypeInput        (CLK_INPUT, STATE_TYPE_TRIGGER);

		setStateTypeOutput (MASTER_RST_OUTPUT, STATE_TYPE_TRIGGER);
		setStateTypeOutput (MASTER_CLK_OUTPUT, STATE_TYPE_TRIGGER);

		setStateTypeOutput (SPH_OUTPUT, STATE_TYPE_TRIGGER);
		setStateTypeOutput (SPA_OUTPUT, STATE_TYPE_TRIGGER);
		setStateTypeOutput (SLAVE_RST_OUTPUT, STATE_TYPE_TRIGGER);
		setStateTypeOutput (SLAVE_CLK_OUTPUT, STATE_TYPE_TRIGGER);
	}

	/**
		Initialize json configuration by defining the lables used form json state variables
	*/
	inline void moduleInitJsonConfig () {

		#pragma GCC diagnostic push 
		#pragma GCC diagnostic ignored "-Wwrite-strings"

		//
		// Config internal Parameters not bound to a user interface object
		//

		setJsonLabel (STYLE_JSON, "style");
		setJsonLabel (RESET_JSON, "reset");
		setJsonLabel (PHRASELENCOUNTER_JSON, "phraseLenCouter");
		setJsonLabel (PHRASEDURCOUNTER_JSON, "phraseDurCounter");
		setJsonLabel (SLAVELENCOUNTER_JSON, "slaveLenCounter");
		setJsonLabel (SLAVEPATTERN_JSON, "slavePattern");
		setJsonLabel (MASTERDELAYCOUNTER_JSON, "masterDelayCounter");
		setJsonLabel (TROWAFIX_JSON, "trowaFix");
		setJsonLabel (DIVCOUNTER_JSON, "divCounter");
		setJsonLabel (CLOCKDELAYCOUNTER_JSON, "clockDelayCounter");
		setJsonLabel (CLOCKWITHRESET_JSON, "clockWithReset");
		setJsonLabel (CLOCKWITHSPA_JSON, "clockWithSpa");
		setJsonLabel (CLOCKWITHSPH_JSON, "clockWithSph");

		#pragma GCC diagnostic pop

		setStateJson (STYLE_JSON, float(STYLE_ORANGE));
		moduleReset();
	}

	/**
		Initialize param configs
	*/
	inline void moduleParamConfig () {	
		configParam (DIV_PARAM,  1.f, 256.f,  1.f, "Clock Division", "",  0.f, 1.f, 0.f);
		configParam (DLY_PARAM,  0.f,  32.f,  1.f, "Master Response Delay", " Samples", 0.f, 1.f, 0.f);
		configParam (LEN_PARAM,  1.f,  64.f, 16.f, "Slave Sequencer Pattern Length", " Steps",  0.f, 1.f, 0.f);
		configParam (INC_PARAM,  MIN_INC, MAX_INC, DEFAULT_INC, "Next Slave Pattern Increment");
		configParam (MASTER_PTN_PARAM, -10.f, 10.f,  0.f, "Master Input Pattern Offset", "",  0.f, 1.f, 0.f);
		configParam (MASTER_PTN_PARAM, -10.f, 10.f,  0.f, "Master Input Pattern Offset", "",  0.f, 1.f, 0.f);
		configParam (CLK_DLY_PARAM,  0.f,  32.f,  0.f, "Slave Clock Delay", " Samples", 0.f, 1.f, 0.f);
	}

	inline void moduleCustomInitialize () {
	}

	/**
		Method to initialize the module after loading a patch or a preset
		Called from initialize () included from from OrangeLineCommon.hpp
		to initialize module state from a valid
		json state after module was added to the patch, 
		a call to dataFromJson due to patch or preset load
		or a right click initialize (reset).
	*/
	inline void moduleInitialize () {
		styleChanged = true;
	}

	/**
		Method to set the module in its initial state after adding to a patch or right click initialize
		Currently called twice when add a module to patch ...
	*/
	void moduleReset () {
		setStateJson (RESET_JSON, 0.f);
		setStateJson (PHRASELENCOUNTER_JSON, 0.f);
		setStateJson (PHRASEDURCOUNTER_JSON, 0.f);
		setStateJson (SLAVELENCOUNTER_JSON, 0.f);
		setStateJson (SLAVEPATTERN_JSON, 0.f);
		setStateJson (MASTERDELAYCOUNTER_JSON, 0.f);
		setStateJson (TROWAFIX_JSON, 0.f);
		setStateJson (DIVCOUNTER_JSON, 0.f);
		setStateJson (CLOCKDELAYCOUNTER_JSON, 0.f);
		setStateJson (CLOCKWITHRESET_JSON, 0.f);
		setStateJson (CLOCKWITHSPA_JSON, 0.f);
		setStateJson (CLOCKWITHSPH_JSON, 0.f);
	}

// ********************************************************************************************************************************
/*
	Module specific utility methods
*/

// ********************************************************************************************************************************
/*
	Methods called directly or indirectly called from process () in OrangeLineCommon.hpp
*/
	void handleStyleChange () {
		if (styleChanged) {
			switch (int(getStateJson (STYLE_JSON))) {
				case STYLE_ORANGE:
					brightPanel->visible = false;
					darkPanel->visible = false;
					break;
				case STYLE_BRIGHT:
					brightPanel->visible = true;
					darkPanel->visible = false;
					break;
				case STYLE_DARK:
					brightPanel->visible = false;
					darkPanel->visible = true;
					break;
			}
			styleChanged = false;
		}
	}

	/*
		(Re)Start the phrase pattern
	*/
	void startPhrasePattern () {
		/*
			Get start pattern number for slave of phrase pattern from master sequencer
		*/
        slavePattern = getStateInput(MASTER_PTN_INPUT) + getStateParam(MASTER_PTN_PARAM);
		if (getStateJson(TROWAFIX_JSON))
			slavePattern = slavePattern + TROWFIX_PATTERN_OFFSET;
		/*
			Set slave sequencer pattern output and
			request slave reset and start pattern trigger with next slave clock
		*/
		clockWithReset = true;
		clockWithSpa   = true;

        setStateOutput (SLAVE_PTN_OUTPUT, slavePattern);

		/*
			Initialize counters for phrase patterns
		*/
		slaveLenCounter  = getStateParam (LEN_PARAM) * getStateParam(DIV_PARAM);
		phraseLenCounter = getStateInput (MASTER_LEN_INPUT) * 100.f;
		if (phraseLenCounter <= 0)
			phraseLenCounter = defaultPhraseLen * 100.f;
	}
	
	void advancePhrasePattern () {
		/*
			Advance slave sequencer to next pattern by incrementing the current slave pattern 
		*/
		slavePattern += getStateParam (INC_PARAM);
		setStateOutput (SLAVE_PTN_OUTPUT, slavePattern);

		slaveLenCounter = getStateParam (LEN_PARAM) * getStateParam(DIV_PARAM);
		/*
			Request e slave reset with next slave clock
		*/
		clockWithReset = true;
	}

	void clockMaster () {
		setStateOutput (MASTER_CLK_OUTPUT, 10.f);
		masterDelayCounter = getStateParam (DLY_PARAM) + 1;
		checkDeferredProcessMaster ();
	}

	void checkDeferredProcessMaster () {
	    if (masterDelayCounter > 0) {
			masterDelayCounter--;
	        if (masterDelayCounter == 0)
				doProcessMaster();
		}
	}

	/*
		Process inputs from master sequencer after reset or end of phrase
		usaualy delayed by 1 or more samples after clocking master sequencer
	*/
	void doProcessMaster() {
		startPhrasePattern ();
		/*
			start the pattern duration
			MUST be executed after startPhrasePattern ()
			because startPhrasePattern sets phraseLenCounter used as default if duration <= 0 below
		*/
        phraseDurCounter = getStateInput (MASTER_DUR_INPUT) * 100.f;
		if (phraseDurCounter <= 0)
			phraseDurCounter = phraseLenCounter;
		/*
			Request start of phrase and slave reset on next slave clock
			(start of pattern and slave reset already requeste by startPhrasePattern above)
		*/
		clockWithSph = true;
		clockSlave();
		/*
			Decrement counters here instead of processing clock triggers because
			we might run asynchronous
		*/
		slaveLenCounter--;
		phraseLenCounter--;
		phraseDurCounter--;
		/*
			Start Div counter
		*/
		divCounter = getStateParam(DIV_PARAM) - 1;
	}

	/*
		Clock slave sequencer 
	*/
	void clockSlave() {
		clockDelayCounter = getStateParam (CLK_DLY_PARAM) + 1;
		checkDeferredClockSlave ();
	}

	void checkDeferredClockSlave () {
        if (clockDelayCounter > 0) {
			clockDelayCounter--;
            if (clockDelayCounter == 0)
				doClockSlave();
       	}
	}

	void doClockSlave() {
		if (clockWithReset)
	        setStateOutput (SLAVE_RST_OUTPUT, 1.0f);
		if (clockWithSpa)
			setStateOutput (SPA_OUTPUT, 1.0f);
		if (clockWithSph)
			setStateOutput (SPH_OUTPUT, 1.0f);
        setStateOutput (SLAVE_CLK_OUTPUT, 1.0f);
		clockWithReset = clockWithSpa = clockWithSph = false;
	}

	/*
		Process reset from this or a previous sample
	*/
	void processPendingReset () {
		if (getStateJson (RESET_JSON) != 0.f) {
			/*
				Set master sequencer pattern number and reset master sequencer
			*/
			setStateOutput (MASTER_PTN_OUTPUT, getStateInput (PTN_INPUT));
			setStateOutput (MASTER_RST_OUTPUT, 10.f);
			/*
				Initialize all counters to 0, forcing further processing
			*/
			phraseDurCounter = 0;
			phraseLenCounter = 0;
			slaveLenCounter  = 0;
			divCounter       = 0;

			setStateJson (RESET_JSON, 0.f);
		}
	}

	/**
		Module specific process method called from process () in OrangeLineCommon.hpp
	*/
	inline void moduleProcess (const ProcessArgs &args) {

		phraseDurCounter   = int(getStateJson (PHRASEDURCOUNTER_JSON));
		phraseLenCounter   = int(getStateJson (PHRASELENCOUNTER_JSON));
		slaveLenCounter    = int(getStateJson (SLAVELENCOUNTER_JSON));
		masterDelayCounter = int(getStateJson (MASTERDELAYCOUNTER_JSON));
		clockDelayCounter  = int(getStateJson (CLOCKDELAYCOUNTER_JSON));
		clockWithReset     = bool(getStateJson (CLOCKWITHRESET_JSON));
		clockWithSpa       = bool(getStateJson (CLOCKWITHSPA_JSON));
		clockWithSph       = bool(getStateJson (CLOCKWITHSPH_JSON));
		slavePattern       = getStateJson (SLAVEPATTERN_JSON);
		divCounter         = getStateJson (DIVCOUNTER_JSON);
		
		/*
			Derive default phrase length from DLEN if connected or LEN*DIV/100 and set effective default phrase length output
		*/
		defaultPhraseLen = 0.f;
		if (getInputConnected(DLEN_INPUT))
			defaultPhraseLen = getStateInput (DLEN_INPUT);
		if (defaultPhraseLen == 0.f)
			defaultPhraseLen = (getStateParam (LEN_PARAM) * getStateParam(DIV_PARAM)) / 100.f;
		setStateOutput (ELEN_OUTPUT, defaultPhraseLen);

		handleStyleChange ();
		checkDeferredProcessMaster();
		checkDeferredClockSlave ();

        if (changeInput (RST_INPUT)) {
            setStateJson (RESET_JSON, 1.f);
        }

        if (changeInput (CLK_INPUT)) {
			processPendingReset ();
			if (phraseDurCounter == 0)
				clockMaster ();
			else {
				if (phraseLenCounter == 0)
					startPhrasePattern ();
				else {
					if (slaveLenCounter == 0) 
						advancePhrasePattern ();
				}
				slaveLenCounter--;
				phraseLenCounter--;
				phraseDurCounter--;

				if (divCounter == 0) {
					clockSlave();
					divCounter = getStateParam(DIV_PARAM);
				}
				divCounter --;
			}
        }
		setStateJson (PHRASEDURCOUNTER_JSON,   float(phraseDurCounter));
		setStateJson (PHRASELENCOUNTER_JSON,   float(phraseLenCounter));
		setStateJson (SLAVELENCOUNTER_JSON,    float(slaveLenCounter));
		setStateJson (MASTERDELAYCOUNTER_JSON, float(masterDelayCounter));
		setStateJson (CLOCKDELAYCOUNTER_JSON,  float(clockDelayCounter));
		setStateJson (CLOCKWITHRESET_JSON,     float(clockWithReset));
		setStateJson (CLOCKWITHSPA_JSON,       float(clockWithSpa));
		setStateJson (CLOCKWITHSPH_JSON,       float(clockWithSph));
		setStateJson (SLAVEPATTERN_JSON,       slavePattern);
		setStateJson (DIVCOUNTER_JSON,         divCounter);
	}

	/**
		Module specific input processing called from process () in OrangeLineCommon.hpp
		right after generic processParamsAndInputs ()

		moduleProcessState () should only be used to derive json state and module member variables
		from params and inputs collected by processParamsAndInputs ().

		This method should not do dsp or other logic processing.
	*/
	inline void moduleProcessState () {
	}	

	/*
		Non standard reflect processing results to user interface components and outputs
	*/
	inline void moduleReflectChanges () {
	}
};

// ********************************************************************************************************************************
/*
	Module widget implementation
*/

/**
	Main Module Widget
*/
struct PhraseWidget : ModuleWidget {

	PhraseWidget(Phrase *module) {

		setModule (module);
		setPanel (APP->window->loadSvg(asset::plugin (pluginInstance, "res/PhraseOrange.svg")));

		if (module) {
			SvgPanel *brightPanel = new SvgPanel();
			brightPanel->setBackground(APP->window->loadSvg(asset::plugin(pluginInstance, "res/PhraseBright.svg")));
			brightPanel->visible = false;
			module->brightPanel = brightPanel;
			addChild(brightPanel);
			SvgPanel *darkPanel = new SvgPanel();
			darkPanel->setBackground(APP->window->loadSvg(asset::plugin(pluginInstance, "res/PhraseDark.svg")));
			darkPanel->visible = false;
			module->darkPanel = darkPanel;
			addChild(darkPanel);
		}

		addInput (createInputCentered<PJ301MPort>   (mm2px (Vec (  3.575 + 4.2 , /* 128.5 - */ 10.874 + 4.2)),  module, RST_INPUT));
		addInput (createInputCentered<PJ301MPort>   (mm2px (Vec ( 13.810 + 4.2 , /* 128.5 - */ 10.874 + 4.2)),  module, CLK_INPUT));
        RoundSmallBlackKnob *knob = createParamCentered<RoundSmallBlackKnob> (mm2px (Vec ( 23.933 + 4.0 , /* 128.5 - */ 11.081 + 4)),    module, DIV_PARAM);
        knob->snap = true;
   		addParam (knob);
		addInput (createInputCentered<PJ301MPort>   (mm2px (Vec ( 33.736 + 4.2 , /* 128.5 - */ 10.874 + 4.2)),  module, PTN_INPUT));

        addOutput (createOutputCentered<PJ301MPort>	(mm2px (Vec (  3.575 + 4.2 , /* 128.5 - */ 31.355 + 4.2)),  module, MASTER_RST_OUTPUT));
        addOutput (createOutputCentered<PJ301MPort>	(mm2px (Vec (  3.575 + 4.2 , /* 128.5 - */ 41.011 + 4.2)),  module, MASTER_CLK_OUTPUT));
        addOutput (createOutputCentered<PJ301MPort>	(mm2px (Vec (  3.575 + 4.2 , /* 128.5 - */ 50.698 + 4.2)),  module, MASTER_PTN_OUTPUT));
        knob = createParamCentered<RoundSmallBlackKnob> (mm2px (Vec ( 3.779 + 4.0 , /* 128.5 - */ 61.553 + 4)), module, DLY_PARAM);
        knob->snap = true;
   		addParam (knob);
        addInput (createInputCentered<PJ301MPort>   (mm2px (Vec (  3.575 + 4.2 , /* 128.5 - */ 71.042 + 4.2)),  module, DLEN_INPUT));
		addParam (createParamCentered<RoundSmallBlackKnob> (mm2px (Vec ( 3.805 + 4.0 , /* 128.5 - */ 80.937 + 4)),    module, MASTER_PTN_PARAM));
        
        addInput (createInputCentered<PJ301MPort>   (mm2px (Vec (  3.575 + 4.2 , /* 128.5 - */ 90.409 + 4.2)),  module, MASTER_PTN_INPUT));
        addInput (createInputCentered<PJ301MPort>   (mm2px (Vec (  3.575 + 4.2 , /* 128.5 - */100.093 + 4.2)),  module, MASTER_LEN_INPUT));
        addInput (createInputCentered<PJ301MPort>   (mm2px (Vec (  3.575 + 4.2 , /* 128.5 - */109.777 + 4.2)),  module, MASTER_DUR_INPUT));
		
        knob = createParamCentered<RoundSmallBlackKnob> (mm2px (Vec (33.941 + 4.0 , /* 128.5 - */ 31.557 + 4)), module, LEN_PARAM);
        knob->snap = true;
   		addParam (knob);

        addOutput (createOutputCentered<PJ301MPort>	(mm2px (Vec ( 33.941 + 4.2 , /* 128.5 - */ 41.011 + 4.2)),  module, ELEN_OUTPUT));
        addParam(createParamCentered<RoundSmallBlackKnob> (mm2px (Vec (33.941 + 4.0 , /* 128.5 - */ 50.932 + 4)), module, INC_PARAM));
        knob = createParamCentered<RoundSmallBlackKnob> (mm2px (Vec ( 33.941 + 4.0 , /* 128.5 - */ 61.553 + 4)), module, CLK_DLY_PARAM);
        knob->snap = true;
   		addParam (knob);

        addOutput (createOutputCentered<PJ301MPort>	(mm2px (Vec ( 33.737 + 4.2 , /* 128.5 - */ 71.041 + 4.2)),  module, SPH_OUTPUT));
        addOutput (createOutputCentered<PJ301MPort>	(mm2px (Vec ( 33.737 + 4.2 , /* 128.5 - */ 80.741 + 4.2)),  module, SPA_OUTPUT));
        addOutput (createOutputCentered<PJ301MPort>	(mm2px (Vec ( 33.737 + 4.2 , /* 128.5 - */ 90.410 + 4.2)),  module, SLAVE_RST_OUTPUT));
        addOutput (createOutputCentered<PJ301MPort>	(mm2px (Vec ( 33.737 + 4.2 , /* 128.5 - */100.093 + 4.2)),  module, SLAVE_CLK_OUTPUT));
        addOutput (createOutputCentered<PJ301MPort>	(mm2px (Vec ( 33.737 + 4.2 , /* 128.5 - */109.777 + 4.2)),  module, SLAVE_PTN_OUTPUT));
	}        

	struct PhraseStyleItem : MenuItem {
		Phrase *module;
		int style;
		void onAction(const event::Action &e) override {
			module->OL_setOutState(STYLE_JSON, float(style));
			module->styleChanged = true;
		}
		void step() override {
			if (module)
				rightText = (module->OL_state[STYLE_JSON] == style) ? "✔" : "";
		}
	};

	struct TrowaFixItem : MenuItem {
		Phrase *module;
		void onAction(const event::Action &e) override {
			float trowaFix = module->OL_state[TROWAFIX_JSON];
			if (trowaFix != 0.f)
				trowaFix = 0.f;
			else
				trowaFix = 1.f;
			module->OL_setOutState(TROWAFIX_JSON, trowaFix);
		}
		void step() override {
			if (module)
				rightText = (module->OL_state[TROWAFIX_JSON] != 0.f) ? "✔" : "";
		}
	};

	void appendContextMenu(Menu *menu) override {
		MenuLabel *spacerLabel = new MenuLabel();
		menu->addChild(spacerLabel);

		Phrase *module = dynamic_cast<Phrase*>(this->module);
		assert(module);

		MenuLabel *styleLabel = new MenuLabel();
		styleLabel->text = "Style";
		menu->addChild(styleLabel);

		PhraseStyleItem *style1Item = new PhraseStyleItem();
		style1Item->text = "Orange";// 
		style1Item->module = module;
		style1Item->style = STYLE_ORANGE;
		menu->addChild(style1Item);

		PhraseStyleItem *style2Item = new PhraseStyleItem();
		style2Item->text = "Bright";// 
		style2Item->module = module;
		style2Item->style = STYLE_BRIGHT;
		menu->addChild(style2Item);
			
		PhraseStyleItem *style3Item = new PhraseStyleItem();
		style3Item->text = "Dark";// 
		style3Item->module = module;
		style3Item->style = STYLE_DARK;
		menu->addChild(style3Item);

		spacerLabel = new MenuLabel();
		menu->addChild(spacerLabel);

		MenuLabel *fixesLabel = new MenuLabel();
		fixesLabel->text = "Fixes";
		menu->addChild(fixesLabel);

		TrowaFixItem *trowaFixItem = new TrowaFixItem();
		trowaFixItem->text = "Trowa pattern offset";// 
		trowaFixItem->module = module;
		menu->addChild(trowaFixItem);
	}
};

Model *modelPhrase = createModel<Phrase, PhraseWidget>("Phrase");
