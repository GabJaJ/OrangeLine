/*
	Dejavu.cpp
 
	Code for the OrangeLine module Dejavu

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
#include <sys/time.h>

#include "Dejavu.hpp"

struct Dejavu : Module {

	#include "OrangeLineCommon.hpp"

	// ********************************************************************************************************************************
	/*
		Module member variables
	*/
	float oldClkInputVoltage = 0;

	struct OrangeLineRandom repeatRandomGenerator[ NUM_ROWS];
	unsigned long                      repeatSeed[ NUM_ROWS];

	struct OrangeLineRandom channelRandomGeneratorGate[POLY_CHANNELS];
	struct OrangeLineRandom   channelRandomGeneratorCv[POLY_CHANNELS];

	#pragma GCC diagnostic push 
	#pragma GCC diagnostic ignored "-Wwrite-strings"

	char *displayHeading = "ACTIVE SEED:";

	#pragma GCC diagnostic pop

	OrangeLineRandom *p_srcRandomGenerator = &globalRandom;
// ********************************************************************************************************************************
/*
	Initialization
*/
	/**
		Constructor

		Typically just calls initializeInstance included from OrangeLineCommon.hpp
	*/
	Dejavu () {
		initializeInstance ();
	}
	/*
		Method to decide whether this call of process() should be skipped
	*/
	bool moduleSkipProcess() {
		bool skip = (idleSkipCounter != 0);
		if (skip) {
			float clkInputVoltage = inputs[CLK_INPUT].getVoltage (); 
			if (clkInputVoltage != oldClkInputVoltage)
				skip = false;
			oldClkInputVoltage = clkInputVoltage;
		}
		return skip;
	}
	/**
		Method to set stateTypes != default types set by initializeInstance() in OrangeLineModule.hpp
		which is called from constructor
	*/
	void moduleInitStateTypes () {
   		setStateTypeInput  (CLK_INPUT, STATE_TYPE_TRIGGER);
   		setStateTypeInput  (RST_INPUT, STATE_TYPE_TRIGGER);

		for (int row = 0; row < NUM_ROWS;row ++)
			setStateTypeParam  (ONOFF_PARAM + row, STATE_TYPE_TRIGGER);

		setInPoly          (REP_INPUT, true);
		setInPoly          (TRG_INPUT, true);

		setOutPoly         (TRG_OUTPUT, true);

		setInPoly          (HEAT_INPUT, true);
		setInPoly          (HEAT_KNOB_ATT_INPUT, true);

		setInPoly          (OFS_INPUT, true);
		setInPoly          (SCL_INPUT, true);

		setStateTypeParam  (SH_PARAM, STATE_TYPE_TRIGGER);
		setInPoly          (SH_INPUT, true);

		setStateTypeParam  (GATE_PARAM, STATE_TYPE_TRIGGER);
		setInPoly          (GATE_INPUT, true);

     	setStateTypeOutput (GATE_OUTPUT, STATE_TYPE_TRIGGER);
		setOutPoly         (GATE_OUTPUT, true);

		setOutPoly         (CV_OUTPUT, true);

#ifdef USE_DEBUG_OUTPUT
		setOutPoly         (DEBUG_OUTPUT, true);
#endif

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
		setJsonLabel (LEN_COUNTER_JSON + 0, "lenConter1");
		setJsonLabel (LEN_COUNTER_JSON + 1, "lenConter2");
		setJsonLabel (LEN_COUNTER_JSON + 2, "lenConter3");
		setJsonLabel (LEN_COUNTER_JSON + 3, "lenConter4");
		setJsonLabel (ONOFF_JSON + 0, "onOff1");
		setJsonLabel (ONOFF_JSON + 1, "onOff2");
		setJsonLabel (ONOFF_JSON + 2, "onOff3");
		setJsonLabel (ONOFF_JSON + 3, "onOff4");
		setJsonLabel (DUR_COUNTER_JSON + 0, "durConter1");
		setJsonLabel (DUR_COUNTER_JSON + 1, "durConter2");
		setJsonLabel (DUR_COUNTER_JSON + 2, "durConter3");
		setJsonLabel (DUR_COUNTER_JSON + 3, "durConter4");
		setJsonLabel (GATE_JSON, "gate");
		setJsonLabel (SH_JSON, "sh");
		setJsonLabel (DIVCOUNTER_JSON, "divCounter");
		setJsonLabel (POLY_CHANNELS_JSON, "polyChannels");

		#pragma GCC diagnostic pop
	}

	/**
		Initialize param configs
	*/
	inline void moduleParamConfig () {
		configParam (DIV_PARAM,             1.f,     DIV_MAX,   1.f, "Clock Division",       "", 0.f, 1.f, 0.f);
		configParam (SEED_PARAM,            0.f,    SEED_MAX,   0.f, "Seed",                 "", 0.f, 1.f, 0.f);
		
		configParam (LEN_PARAM + 0,       1.f,     MAX_REP,   1.f, "Length 1",               "", 0.f, 1.f, 0.f);
		configParam (LEN_PARAM + 1,       1.f,     MAX_REP,   1.f, "Length 2",               "", 0.f, 1.f, 0.f);
		configParam (LEN_PARAM + 2,       1.f,     MAX_REP,   1.f, "Length 3",               "", 0.f, 1.f, 0.f);
		configParam (LEN_PARAM + 3,       1.f,     MAX_REP,   1.f, "Length 4",               "", 0.f, 1.f, 0.f);		
 
   		configParam (ONOFF_PARAM + 0,     0.f,         1.f,   0.f, "Repeater 1 On/Offf",     "", 0.f, 1.f, 0.f);
   		configParam (ONOFF_PARAM + 1,     0.f,         1.f,   0.f, "Repeater 2 On/Offf",     "", 0.f, 1.f, 0.f);
   		configParam (ONOFF_PARAM + 2,     0.f,         1.f,   0.f, "Repeater 3 On/Offf",     "", 0.f, 1.f, 0.f);
   		configParam (ONOFF_PARAM + 3,     0.f,         1.f,   0.f, "Repeater 4 On/Offf",     "", 0.f, 1.f, 0.f);

		configParam (DUR_PARAM + 0,       1.f,     MAX_REP,   1.f, "Duration 1",             "", 0.f, 1.f, 0.f);
		configParam (DUR_PARAM + 1,       1.f,     MAX_REP,   1.f, "Duration 2",             "", 0.f, 1.f, 0.f);
		configParam (DUR_PARAM + 2,       1.f,     MAX_REP,   1.f, "Duration 3",             "", 0.f, 1.f, 0.f);
		configParam (DUR_PARAM + 3,       1.f,     MAX_REP,   1.f, "Duration 4",             "", 0.f, 1.f, 0.f);		

		configParam (HEAT_PARAM,            0.f,       100.f,  50.f, "Heat",                 "%", 0.f, 1.f, 0.f);
		
		configParam (OFS_PARAM,           -10.f,        10.f,   0.f, "Offset",               "",  0.f, 1.f, 0.f);
		configParam (OFS_ATT_PARAM,      -100.f,       100.f,   0.f, "Offset Attenuation",   "%", 0.f, 1.f, 0.f);
		
		configParam (SCL_PARAM,          -100.f,       100.f, 100.f, "Scale",                "",  0.f, 1.f, 0.f);
		configParam (SCL_ATT_PARAM,      -100.f,       100.f,   0.f, "Scale Attenuation",    "%", 0.f, 1.f, 0.f);

		configParam (CHN_PARAM,             1.f,        16.f,   1.f, "# of Output Channels", "", 0.f, 1.f, 0.f);

   		configParam (SH_PARAM,              0.f,         1.f,   0.f,  "Toggle CV S&H",       "", 0.f, 1.f, 0.f);
   		configParam (GATE_PARAM,            0.f,         1.f,   0.f,  "Toggle Trigger/Gate", "", 0.f, 1.f, 0.f);
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
	*/
	void moduleReset () {
		setStateJson (RESET_JSON,       0.f);
		setStateJson (LEN_COUNTER_JSON + 0, 0.f);
		setStateJson (LEN_COUNTER_JSON + 1, 0.f);
		setStateJson (LEN_COUNTER_JSON + 2, 0.f);
		setStateJson (LEN_COUNTER_JSON + 3, 0.f);
		setStateJson (ONOFF_JSON + 0, 0.f);
		setStateJson (ONOFF_JSON + 1, 0.f);
		setStateJson (ONOFF_JSON + 2, 0.f);
		setStateJson (ONOFF_JSON + 3, 0.f);
		setStateJson (DUR_COUNTER_JSON + 0, 0.f);
		setStateJson (DUR_COUNTER_JSON + 1, 0.f);
		setStateJson (DUR_COUNTER_JSON + 2, 0.f);
		setStateJson (DUR_COUNTER_JSON + 3, 0.f);
		setStateJson (GATE_JSON, TRIGGER_MODE);
		setStateJson (SH_JSON, 0.f);
		setStateJson (DIVCOUNTER_JSON, 0.f);
		setStateJson (POLY_CHANNELS_JSON, 1.f);
	}

#ifdef USE_DEBUG_OUTPUT
void debugOutput (int channel, float value) {
	setOutPolyChannels (DEBUG_OUTPUT, 16);
	OL_statePoly[NUM_INPUTS * POLY_CHANNELS + DEBUG_OUTPUT * POLY_CHANNELS + channel - 1] = value;
	OL_outStateChangePoly[DEBUG_OUTPUT * POLY_CHANNELS + channel - 1] = true;
}
#endif


// ********************************************************************************************************************************
/*
	Module specific utility methods
*/

// ********************************************************************************************************************************
/*
	Initialize global random generator 
	initializerepeatRandomGenerators
	Set all counters to 0 on reset
*/
	void doReset () {
		float seed = 0; 
		if (getInputConnected (SEED_INPUT)) {
			float seedFloat = getStateInput (SEED_INPUT) * SEED_INPUT_SCALE;
			if (seedFloat < 0)
				seedFloat *= -1;
			unsigned long seed = (unsigned long)seedFloat;
			if (seed > SEED_MAX)
				seed = SEED_MAX;
			setStateParam (SEED_PARAM, float(seed));
		}
		else
			seed = getStateParam (SEED_PARAM);

		initRandom (&globalRandom, seed);

		for (int i = 0; i <  NUM_ROWS; i ++) {
			setStateJson (LEN_COUNTER_JSON + i, 0.f);
			setStateJson (DUR_COUNTER_JSON + i, 0.f);
			initRandom (&(repeatRandomGenerator[i]), getRandomRaw(&globalRandom));
		}
	}

	int getRepCount (int baseIdx, int row) {

		if (int(getStateJson (ONOFF_PARAM + row)) == 0 || 
			(int(getStateParam (LEN_PARAM + row)) == 1 && int(getStateParam (DUR_PARAM + row)) == 1)) {
				// we are inactive so only called due to get factor for an active one above
				if (row == 0)
					// if we are the lowerst just return 1 for the multiply factor
					return 1;
				else
					// propagate the call down a level
					return 	getRepCount (baseIdx, row - 1);
		}
		int count = getRepCountFromInput (baseIdx, row);
		if (count == 0)
			count = calculateCount (baseIdx, row, int(getStateParam (baseIdx + row)));
		if (count < 1)
			count = 1;
		return count;
	}

	int getRepCountFromInput (int row, int i) {
		if (! getInputConnected (REP_INPUT))
			return 0;
		int channels = inputs[REP_INPUT].getChannels();
		if (row > channels)
			return 0;
		// REP_INPUT is polyphonic
		// Channels 1 to  NUM_ROWS are interpreted in the same way as the Knobs
		// Channels  NUM_ROWS + 1 to  NUM_ROWS * 2 are take lietrally allowing uneven patterns of repition
		// index is 0 based
		int rep = int(OL_statePoly[REP_INPUT * POLY_CHANNELS + row] * REP_INPUT_SCALE);
		if (rep != 0)
			return calculateCount (REP_INPUT, row, rep);
		if (row +  NUM_ROWS > channels)
			return 0;
		rep = OL_statePoly[REP_INPUT * POLY_CHANNELS + row +  NUM_ROWS] * REP_INPUT_SCALE;
		if (rep == 0)
			return 0;
		return rep;
	}
	
	int calculateCount (int baseIdx, int row, int count) {
		if (row == 0)
			return count;
		else {
			if (baseIdx == LEN_COUNTER_JSON)
				baseIdx = DUR_COUNTER_JSON;
			return count * getRepCount (baseIdx, row - 1);
		}
	}

	bool rowActive (int row) {
		if (int(getStateJson (ONOFF_PARAM + row)) == 0 || 
			(int(getStateParam (LEN_PARAM + row)) == 1 && int(getStateParam (DUR_PARAM + row)) == 1))
			return false;
		return true;
	}
/*
	Methods called directly or indirectly called from process () in OrangeLineCommon.hpp
*/
	/**
		Module specific process method called from process () in OrangeLineCommon.hpp
	*/
	inline void moduleProcess (const ProcessArgs &args) {
		if (styleChanged) {
			switch (int(getStateJson(STYLE_JSON))) {
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

		if (changeInput (RST_INPUT))
			doReset();

		// handle polyphonic TRG_INPUT
		if (getInputConnected (TRG_INPUT)) {
			int channels = inputs[TRG_INPUT].getChannels();
			for (int channel =  NUM_ROWS - 1; channel >= 0; channel--) {
				if (channel > channels)
					break;
				if (OL_inStateChangePoly[TRG_INPUT * POLY_CHANNELS + channel]) { 
					setStateJson (DUR_COUNTER_JSON + channel, 0.f);
					break;
				}
			}
		}

		if (changeInput (CLK_INPUT)) {

			if (int(getStateJson (DIVCOUNTER_JSON)) == 0) {
				setStateJson (DIVCOUNTER_JSON, getStateParam(DIV_PARAM));

				p_srcRandomGenerator = &globalRandom;
				for (int row =  NUM_ROWS - 1; row >= 0; row --) {

					if (!rowActive (row))
						continue;	// Nothing to do here

					// We still have to run nothing if this row iswitched off to keep trak of the counter? NO!!!!

					int durCount = int(getStateJson (DUR_COUNTER_JSON + row));
					int lenCount = int(getStateJson (LEN_COUNTER_JSON + row));

					if (durCount == 0) {
						// DEBUG("durCount == 0 for row %d", row);
						repeatSeed[row] = getRandomRaw (p_srcRandomGenerator);
						durCount = getRepCount (DUR_COUNTER_JSON, row);
						// DEBUG("durCount reinitialited to %d for row %d", durCount, row);
						lenCount = 0; // force a length reset off this row 
					}

					if (lenCount == 0){
						// DEBUG("lenCount == 0 for row %d", row);
						initRandom (&(repeatRandomGenerator[row]), repeatSeed[row]);
						lenCount = getRepCount(LEN_COUNTER_JSON, row);
						// DEBUG("lenCount reinitialited to %d for row %d", lenCount, row);
						if (row > 0)
							setStateJson (DUR_COUNTER_JSON + row - 1, 0.f); // force duration reset the row below
					}

					// DEBUG("p_srcRandomGenerator = &(repeatRandomGenerator[%d]);", row);
					p_srcRandomGenerator = &(repeatRandomGenerator[row]);

					durCount--;
					setStateJson (DUR_COUNTER_JSON + row, durCount);

					lenCount--;
					setStateJson (LEN_COUNTER_JSON + row, lenCount);
				}

				// Reinitialize Gate and CV random generators
				// ge a new seed from the srcRandomGenerator 
				// DEBUG("channelRandomGenerator initialized from lengthRandomGenerator[0] seed : % 8lX", seed);
				// get the seed for the next one by advancing the last initialized one for diversity
				// all generators would work in sync otherwise
				// We intensionally do not use POLY_CHANNELS_JSON here but use POLY_CHANNELS constan 16 here to 
				// not change random pattern due to changing the number of poly channels
				unsigned long seed = getRandomRaw (p_srcRandomGenerator);
				for (int channel = 0; channel < POLY_CHANNELS; channel ++) {
					initRandom (&(channelRandomGeneratorGate[channel]), seed);
					initRandom (&(channelRandomGeneratorCv[channel]), getRandomRaw (&(channelRandomGeneratorGate[channel])));
					seed = getRandomRaw (&(channelRandomGeneratorCv[channel]));
				}
				/*
					Process output channels
				*/
				setOutPolyChannels(GATE_OUTPUT, getStateJson(POLY_CHANNELS_JSON));
				setOutPolyChannels(CV_OUTPUT, getStateJson(POLY_CHANNELS_JSON));
				int heatPolyChannels = inputs[HEAT_INPUT].getChannels();
				int ofsPolyChannels = inputs[OFS_INPUT].getChannels();
				int sclPolyChannels = inputs[SCL_INPUT].getChannels();
				int knbPolyChannels = inputs[HEAT_KNOB_ATT_INPUT].getChannels();
				float lastHeatInput = 0;
				float lastOfsInput = 0;
				float lastSclInput = 0;
				float lastKnbInput = 0;
				float lastShValue = 0;
				for (int channel = 0; channel < getStateJson(POLY_CHANNELS_JSON); channel ++) {
					float gateRandom = getRandom (&(channelRandomGeneratorGate[channel]));
					float heat = getStateParam(HEAT_PARAM) / 100.f;
					bool fired = false;
					if (getInputConnected(HEAT_INPUT)) {
						float heatInput = 0.f;

						if (channel > heatPolyChannels)
							heatInput = lastHeatInput;
						else {
							heatInput = OL_statePoly[HEAT_INPUT * POLY_CHANNELS + channel] / 10.f;
							lastHeatInput = heatInput;
						}

						if (getInputConnected(HEAT_KNOB_ATT_INPUT)) {
							float knobAttInput = 1.f;
							if (channel > knbPolyChannels)
								knobAttInput = lastKnbInput;
							else {
								knobAttInput = OL_statePoly[HEAT_KNOB_ATT_INPUT * POLY_CHANNELS + channel] / 10.f;
								lastKnbInput = knobAttInput;
							}
							heat *= knobAttInput;
						}
						heat +=  heatInput;
					}
					if (heat >= gateRandom) {
						OL_statePoly[ NUM_INPUTS * POLY_CHANNELS + GATE_OUTPUT * POLY_CHANNELS + channel] = 10.f;
						OL_outStateChangePoly[GATE_OUTPUT * POLY_CHANNELS + channel] = true;
						fired = true;
					}
					if (fired) {
						bool sh = (getStateJson(SH_JSON) == 1.f);
						if (getInputConnected(SH_INPUT)) {
							float value = lastShValue;
							if (channel > inputs[SH_INPUT].getChannels()) {
								value = OL_statePoly[SH_INPUT * POLY_CHANNELS + channel];
							}
							lastShValue = value;
							sh = (value > 5.f);
						}
						if (!sh) {
							float cvRandom = -10.f + getRandom (&(channelRandomGeneratorCv[channel])) * 20.f;
							float scl = getStateParam (SCL_PARAM) / 100.f;
							if (getInputConnected (SCL_INPUT)) {
								int sclInput = 0.f;
								if (channel > sclPolyChannels)
									sclInput = lastSclInput;
								else {
									sclInput = OL_statePoly[SCL_INPUT * POLY_CHANNELS + channel];
									lastSclInput = sclInput;
								}
								scl += (getStateParam(SCL_ATT_PARAM) / 100.f) * sclInput / 10.f;
							}
							cvRandom *= scl;
							float ofs = getStateParam (OFS_PARAM);
							if (getInputConnected (OFS_INPUT)) {
								int ofsInput = 0.f;
								if (channel > ofsPolyChannels)
									ofsInput = lastOfsInput;
								else {
									ofsInput = OL_statePoly[OFS_INPUT * POLY_CHANNELS + channel];
									lastOfsInput = ofsInput;
								}
								ofs += (getStateParam(OFS_ATT_PARAM) / 100.f) * ofsInput;
							}
							cvRandom += ofs;
							cvRandom = clamp (cvRandom, -10.f, 10.f);
							OL_statePoly[NUM_INPUTS * POLY_CHANNELS + CV_OUTPUT * POLY_CHANNELS + channel] = cvRandom;
							OL_outStateChangePoly[CV_OUTPUT * POLY_CHANNELS + channel] = true;
						}
					}
				}	
			}	
			setStateJson(DIVCOUNTER_JSON, getStateJson(DIVCOUNTER_JSON) - 1);
		}
	}

	/**
		Module specific input processing called from process () in OrangeLineCommon.hpp
		right after generic processParamsAndInputs ()

		moduleProcessState () should only be used to derive json state and module member variables
		from params and inputs collected by processParamsAndInputs ().

		This method should not do dsp or other logic processing.
	*/
	inline void moduleProcessState () {
		if (inChangeParam (GATE_PARAM))	{
			setStateJson (GATE_JSON, float((int(getStateJson (GATE_JSON)) + 1) % 2));
		}

		if (getStateJson (GATE_JSON) > 0.f)
			isGate (GATE_OUTPUT) = true;
		else
			isGate (GATE_OUTPUT) = false;

		for (int row = 0; row <  NUM_ROWS; row++) {
			if (inChangeParam (ONOFF_PARAM + row))
				setStateJson (ONOFF_JSON + row, float((int(getStateJson (ONOFF_JSON + row)) + 1) % 2));
		}

		if (inChangeParam (SH_PARAM))	{
			setStateJson (SH_JSON, float((int(getStateJson (SH_JSON)) + 1) % 2));
		}
	}

	/*
		Non standard reflect processing results to user interface components and outputs
	*/
	inline void moduleReflectChanges () {

		if (getInputConnected (GATE_INPUT)) {
			int channels = inputs[GATE_INPUT].getChannels();
			float lastValue = 0;
			for (int channel = 0; channel < POLY_CHANNELS; channel ++) {
				int value;
				if (channel > channels)
					value = lastValue;
				else
					value = OL_statePoly[GATE_INPUT * POLY_CHANNELS + channel];
				OL_isGatePoly[GATE_OUTPUT * POLY_CHANNELS_JSON + channel] = value;
				lastValue = value;
			}
		}

		for (int row = 0; row < NUM_ROWS; row++) {
			if (getStateJson (ONOFF_JSON + row) == 1.) {
				if (int(getStateParam (LEN_PARAM + row)) == 1 && int(getStateParam (DUR_PARAM + row)) == 1)
					setRgbLight (REP_LIGHT_RGB + (3 * row), ONOFF_COLOR_ON_INACTIVE);
				else
					setRgbLight (REP_LIGHT_RGB + (3 * row), ONOFF_COLOR_ON);
			}
			else
				setRgbLight (REP_LIGHT_RGB + (3 * row), ONOFF_COLOR_OFF);
		}

		if (getStateJson (GATE_JSON) == 1.)
			setRgbLight (GATE_LIGHT_RGB, GATE_COLOR_ON);
		else
			setRgbLight (GATE_LIGHT_RGB, GATE_COLOR_OFF);

		if (getStateJson (SH_JSON) == 1.)
			setRgbLight (SH_LIGHT_RGB, SH_COLOR_ON);
		else
			setRgbLight (SH_LIGHT_RGB, SH_COLOR_OFF);
	}
};

// ********************************************************************************************************************************
/*
	Module widget implementation
*/
// Creates new circle arc shaped sub-path. The arc center is at cx,cy, the arc radius is r,
// and the arc is drawn from angle a0 to a1, and swept in direction dir (NVG_CCW, or NVG_CW).
// Angles are specified in radians.
// void nvgArc(NVGcontext* ctx, float cx, float cy, float r, float a0, float a1, int dir);

/**
	Widget to display cvOct values as floats or notes
*/
struct LeftWidget : TransparentWidget {

	std::shared_ptr<Font> pFont;

	Dejavu     *module = nullptr;
	int       paramDisplayCycles = 0;

	static LeftWidget* create (Dejavu *module) {
		LeftWidget *w = new LeftWidget();

		w->pFont    = APP->window->loadFont(asset::plugin(pluginInstance, "res/repetition-scrolling.regular.ttf"));
		w->box.pos  = mm2px (Vec (1.524, 36.831));
		w->box.size = mm2px (Vec (32.512, 10.668));
		// w->box.pos.y += w->box.size.y;
		w->module   = module;

		return w;
	}

	/**
		Constructor
	*/
	LeftWidget () {
	}

	void draw (const DrawArgs &drawArgs) override {
		if (module) {
			float style = module->getStateJson(STYLE_JSON);
			char headBuffer[18];
			char valueBuffer[18];
			headBuffer[17] = '\0';
			valueBuffer[17] = '\0';

			//nvgBeginPath(drawArgs.vg);
			//nvgFillColor (drawArgs.vg, nvgRGB(0, 0, 255));
			//nvgRect(drawArgs.vg, 0, 0, box.size.x, box.size.y);
			//nvgFill(drawArgs.vg);

			if (module->paramChanged) {
				paramDisplayCycles = PARAM_DISPLAY_CYCLES;
				module->paramChanged = false;
			} 
			if (paramDisplayCycles > 0) {
				int param = module->lastParamChanged;
				ParamQuantity *pq = module->paramQuantities[param];
				const char *label = pq->label.data();
				const char *unit  = pq->unit.data();
				if (*unit != '\0')
					snprintf (headBuffer, 17, "%s[%s]:", label, unit);
				else
					snprintf (headBuffer, 17, "%s:", label);
				float value = module->getStateParam(param);
				if (value == float(int(value)))
					snprintf (valueBuffer, 17, "%8.0lf", module->getStateParam(param));
				else
					snprintf (valueBuffer, 17, "%8.3lf", module->getStateParam(param));

				paramDisplayCycles --;
			}
			else {
				if (module->p_srcRandomGenerator != nullptr) {
					strncpy (headBuffer, module->displayHeading, 17);
					sprintf (valueBuffer, "%08lX", module->p_srcRandomGenerator->latest_seed);
				}
				else {
					strcpy(valueBuffer, "null");
				}
			}
			nvgFontFaceId (drawArgs.vg, pFont->handle);
			nvgFontSize (drawArgs.vg, 20);
			nvgFillColor (drawArgs.vg, (style == STYLE_ORANGE) ? ORANGE : WHITE);
			nvgText (drawArgs.vg, mm2px(2.447) - box.pos.x + mm2px(0.5), mm2px(41.283) - box.pos.y + mm2px(4.812), valueBuffer, nullptr);

			nvgFontSize (drawArgs.vg, 10);
			nvgText (drawArgs.vg, mm2px(0.5), mm2px(0.5) + mm2px(2.406), headBuffer, nullptr);
			//nvgText (drawArgs.vg, mm2px(2.447) - box.pos.x + mm2px(0.5), mm2px(41.283) - box.pos.y + mm2px(4.812), valueBuffer, nullptr);
		}
	}
};

#define PI 3.14159265

struct RigthWidget : TransparentWidget {

	std::shared_ptr<Font> pFont;

	Dejavu     *module = nullptr;

	static RigthWidget* create (Dejavu *module) {
		RigthWidget *w = new RigthWidget();

		w->pFont    = APP->window->loadFont(asset::plugin(pluginInstance, "res/repetition-scrolling.regular.ttf"));
		w->box.pos  = mm2px (Vec (37.084, 8.891));
		w->box.size = mm2px (Vec (32.512, 38.608));
		w->module   = module;

		return w;
	}

	/**
		Constructor
	*/
	RigthWidget () {
	}

	void drawCircle(NVGcontext *nvg, float x, float y, float radius, NVGcolor color, float strokeWidth) {
		nvgBeginPath (nvg);
		nvgCircle (nvg, x, y, radius);

		if (strokeWidth == 0){
			nvgFillColor (nvg, color);
			nvgFill (nvg);
		}
		else {
			nvgStrokeColor (nvg, color);
			nvgStrokeWidth (nvg, strokeWidth);
			nvgStroke(nvg);
		}
	}

	void draw (const DrawArgs &drawArgs) override {
		if (module) {
			nvgGlobalCompositeOperation(drawArgs.vg, NVG_SOURCE_OVER);
			nvgGlobalCompositeBlendFunc(drawArgs.vg, NVG_SRC_COLOR, NVG_ZERO);

			// float style = module->getStateJson(STYLE_JSON);

			//nvgBeginPath(drawArgs.vg);
			//nvgFillColor (drawArgs.vg, nvgRGB(0, 0, 255));
			//nvgRect(drawArgs.vg, 0, 0, box.size.x, box.size.y);
			//nvgFill(drawArgs.vg);

			NVGcolor dotColor[4] = {
				nvgRGBA (0x99, 0x00, 0xff, 0xff),
				nvgRGBA (0x00, 0xff, 0x00, 0xff),
				nvgRGBA (0xff, 0xff, 0x66, 0xff),
				nvgRGBA (0xff, 0x88, 0x00, 0xff)
			};
			int trackAlpha = 0xbb;
			NVGcolor trackColor[4] = {
				nvgRGBA (0x00, 0x00, 0xff, trackAlpha),
				nvgRGBA (0x00, 0xff, 0x00, trackAlpha),
				nvgRGBA (0xff, 0xff, 0x66, trackAlpha),
				nvgRGBA (0xff, 0x88, 0x00, trackAlpha)
			};

			float maxTrackRadius   = (box.size.x / 2) - mm2px(1.f);
			float radiusDistance   = mm2px(2.5f);
			float radiusDot        = 2.f;
			float trackStrokeWidth = 1.f;

			Vec center = Vec(box.size.x / 2, box.size.y / 2);
			float levelRadius = maxTrackRadius; 
			for (int level = NUM_ROWS - 1;level >= 0; level--) {
				if (module->rowActive(level)) {
					drawCircle(drawArgs.vg, center.x, center.y, levelRadius, trackColor[NUM_ROWS - 1 - level], trackStrokeWidth);
					int durCount = module->getRepCount(DUR_PARAM, + level);
					int lenCount = module->getRepCount(LEN_PARAM, + level);
					float cycles = (float(durCount) / float(lenCount));
					float radAlpha  = (2 * PI) / cycles;
					int point = 0;
					for (; float(point) < cycles; point ++) {
						float x = sin (radAlpha * point + PI) * levelRadius;
						float y = cos (radAlpha * point + PI) * levelRadius;
						drawCircle(drawArgs.vg, x + center.x, y + center.y, radiusDot, dotColor[NUM_ROWS - 1 - level], 0);
					}
				}
				levelRadius -= radiusDistance;
			}
		}
	}
};
/**
	Main Module Widget
*/
#define PANELHEIGHT 128.5f
#define OFFSET_PJ301MPort 4.2
#define OFFSET_Trimpot 3.15
#define OFFSET_RoundSmallBlackKnob 4.0
#define OFFSET_RoundHugeBlackKnob 9.5
#define OFFSET_LargeLight 4.762 / 2
#define OFFSET_LEDButton 4.762 / 2
#define OFFSET_RoundLargeBlackKnob 12.7 / 2

#define calculateCoordinates(x, y, offset) mm2px (Vec (x + offset ,  y + offset))

struct DejavuWidget : ModuleWidget {

	DejavuWidget(Dejavu *module) {
        RoundSmallBlackKnob *knob;
		LargeLight<RedGreenBlueLight> *light;
        setModule (module);
		setPanel (APP->window->loadSvg(asset::plugin (pluginInstance, "res/DejavuOrange.svg")));

		if (module) {
			SvgPanel *brightPanel = new SvgPanel();
			brightPanel->setBackground(APP->window->loadSvg(asset::plugin(pluginInstance, "res/DejavuBright.svg")));
			brightPanel->visible = false;
			
			module->brightPanel = brightPanel;
			addChild(brightPanel);
			SvgPanel *darkPanel = new SvgPanel();
			darkPanel->setBackground(APP->window->loadSvg(asset::plugin(pluginInstance, "res/DejavuDark.svg")));
			darkPanel->visible = false;
			module->darkPanel = darkPanel;
			addChild(darkPanel);
		}
		
		addInput (createInputCentered<PJ301MPort> (calculateCoordinates ( 3.415, 12.125, OFFSET_PJ301MPort), module,  RST_INPUT));
		addInput (createInputCentered<PJ301MPort> (calculateCoordinates ( 3.415, 22.212, OFFSET_PJ301MPort), module,  CLK_INPUT));
		addInput (createInputCentered<PJ301MPort> (calculateCoordinates (13.575, 12.125, OFFSET_PJ301MPort), module,  DIV_INPUT));
		addInput (createInputCentered<PJ301MPort> (calculateCoordinates (13.575, 22.212, OFFSET_PJ301MPort), module, SEED_INPUT));
		knob = createParamCentered<RoundSmallBlackKnob> (calculateCoordinates (23.940, 12.258, OFFSET_RoundSmallBlackKnob),  module, DIV_PARAM);
        knob->snap = true;
   		addParam (knob);
		knob = createParamCentered<RoundSmallBlackKnob> (calculateCoordinates (23.940, 22.418, OFFSET_RoundSmallBlackKnob),  module, SEED_PARAM);
        knob->snap = true;
		addParam (knob);

		for (int i = 0; i <  NUM_ROWS; i ++) {
			float y = 54.168 + (10.16 * i);
			float yb = 55.786 + (10.16 * i);
			knob = createParamCentered<RoundSmallBlackKnob> (calculateCoordinates (3.62, y, OFFSET_RoundSmallBlackKnob),  module, LEN_PARAM + i);
	        knob->snap = true;
			addParam (knob);
			addParam (createParamCentered<LEDButton> (calculateCoordinates (15.399, yb, OFFSET_LEDButton), module, ONOFF_PARAM + i));
			light = createLightCentered<LargeLight<RedGreenBlueLight>> (calculateCoordinates (15.399, yb, OFFSET_LargeLight), module, REP_LIGHT_RGB + (3 * i));
			light->bgColor = nvgRGBA(0, 0, 0, 255);
			addChild (light);
			knob = createParamCentered<RoundSmallBlackKnob> (calculateCoordinates (23.940, y, OFFSET_RoundSmallBlackKnob),  module, DUR_PARAM + i);
	        knob->snap = true;
			addParam (knob);
		}

		addInput (createInputCentered<PJ301MPort> (calculateCoordinates (3.415, 99.682, OFFSET_PJ301MPort), module, REP_INPUT));
		addOutput (createOutputCentered<PJ301MPort>	(calculateCoordinates (23.940, 99.682, OFFSET_PJ301MPort),  module, REP_OUTPUT));

		addInput (createInputCentered<PJ301MPort> (calculateCoordinates (3.415, 109.842, OFFSET_PJ301MPort), module, TRG_INPUT));
		addOutput (createOutputCentered<PJ301MPort>	(calculateCoordinates (23.940, 109.842, OFFSET_PJ301MPort),  module, TRG_OUTPUT));

		addInput (createInputCentered<PJ301MPort> (calculateCoordinates (38.975, 52.438, OFFSET_PJ301MPort), module, HEAT_INPUT ));
		addInput (createInputCentered<PJ301MPort> (calculateCoordinates (59.295, 52.438, OFFSET_PJ301MPort), module, HEAT_KNOB_ATT_INPUT ));
		addParam (createParamCentered<RoundLargeBlackKnob> (calculateCoordinates (46.990, 57.659, OFFSET_RoundLargeBlackKnob),  module, HEAT_PARAM));
		addParam (createParamCentered<RoundSmallBlackKnob> (calculateCoordinates (39.180, 79.568, OFFSET_RoundSmallBlackKnob),  module, OFS_PARAM));
		addParam (createParamCentered<RoundSmallBlackKnob> (calculateCoordinates (49.340, 79.568, OFFSET_RoundSmallBlackKnob),  module, SCL_PARAM));
		addParam (createParamCentered<Trimpot> (calculateCoordinates ( 40.030, 90.577, OFFSET_Trimpot),  module, OFS_ATT_PARAM));
		addParam (createParamCentered<Trimpot> (calculateCoordinates ( 50.190, 90.577, OFFSET_Trimpot),  module, SCL_ATT_PARAM));
		addInput (createInputCentered<PJ301MPort> (calculateCoordinates (38.975, 99.682, OFFSET_PJ301MPort), module, OFS_INPUT ));
		addInput (createInputCentered<PJ301MPort> (calculateCoordinates (49.135, 99.682, OFFSET_PJ301MPort), module, SCL_INPUT ));
		addInput (createInputCentered<PJ301MPort> (calculateCoordinates (59.295, 89.522, OFFSET_PJ301MPort), module, SH_INPUT ));
		addInput (createInputCentered<PJ301MPort> (calculateCoordinates (49.135, 109.842, OFFSET_PJ301MPort), module, GATE_INPUT ));
		addOutput (createOutputCentered<PJ301MPort>	(calculateCoordinates (59.295, 99.682, OFFSET_PJ301MPort),  module, CV_OUTPUT));
		addOutput (createOutputCentered<PJ301MPort>	(calculateCoordinates (59.295, 109.842, OFFSET_PJ301MPort),  module, GATE_OUTPUT));

		addParam (createParamCentered<LEDButton>                   (calculateCoordinates (61.210, 81.186, OFFSET_LEDButton), module, SH_PARAM));
		light = createLightCentered<LargeLight<RedGreenBlueLight>> (calculateCoordinates (61.120, 81.186, OFFSET_LargeLight), module, SH_LIGHT_RGB);
		light->bgColor = nvgRGBA(0, 0, 0, 255);
	 	addChild (light);

		addParam (createParamCentered<LEDButton>                   (calculateCoordinates (40.800, 111.666, OFFSET_LEDButton), module, GATE_PARAM));
		light = createLightCentered<LargeLight<RedGreenBlueLight>> (calculateCoordinates (40.800, 111.666, OFFSET_LargeLight), module, GATE_LIGHT_RGB);
		light->bgColor = nvgRGBA(0, 0, 0, 255);
	 	addChild (light);

 		addChild (LeftWidget::create (module));
 		addChild (RigthWidget::create (module));

#ifdef USE_DEBUG_OUTPUT
		addOutput (createOutputCentered<PJ301MPort>	(calculateCoordinates (0, 0, OFFSET_PJ301MPort),  module, DEBUG_OUTPUT));
#endif
	}

	struct DejavuStyleItem : MenuItem {
		Dejavu *module;
		int style;
		void onAction(const event::Action &e) override {
			module->OL_setOutState(STYLE_JSON, float(style));
			module->styleChanged = true;
		}
		void step() override {
			if (module)
				rightText = (module != nullptr && module->OL_state[STYLE_JSON] == style) ? "✔" : "";
		}
	};

    struct PolyChannelsItem : MenuItem {
    Dejavu *module;

   		struct PolyChannelItem : MenuItem {
        	Dejavu *module;
        	int channels;
        	void onAction(const event::Action &e) override {
           		module->OL_setOutState(POLY_CHANNELS_JSON, float(channels));
        	}
        	void step() override {
            	if (module)
            		rightText = (module != nullptr && module->OL_state[POLY_CHANNELS_JSON] == channels) ? "✔" : "";
        	}
    	};

        Menu *createChildMenu() override {
            Menu *menu = new Menu;
			PolyChannelItem *polyChannelItem;
			for (int channel = 0; channel < 16; channel++) {
				polyChannelItem = new PolyChannelItem ();
				polyChannelItem->module = module;
				polyChannelItem->channels = channel + 1;
				polyChannelItem->text = module->channelNumbers[channel];
				polyChannelItem->setSize (Vec(50, 20));
				menu->addChild(polyChannelItem);
			}
			return menu;
		}
    };

	void appendContextMenu(Menu *menu) override {
		if (module) {
			MenuLabel *spacerLabel = new MenuLabel();
			menu->addChild(spacerLabel);

			Dejavu *module = dynamic_cast<Dejavu*>(this->module);
			assert(module);

			spacerLabel = new MenuLabel();
			menu->addChild(spacerLabel);

			MenuLabel *polyphonyLabel = new MenuLabel();
			polyphonyLabel->text = "Polyphony";
			menu->addChild(polyphonyLabel);

			PolyChannelsItem *polyChannelsItem = new PolyChannelsItem();
			polyChannelsItem->module = module;
			polyChannelsItem->text = "Poly Channels";
			polyChannelsItem->rightText = RIGHT_ARROW;
			menu->addChild(polyChannelsItem);

			spacerLabel = new MenuLabel();
			menu->addChild(spacerLabel);

			spacerLabel = new MenuLabel();
			menu->addChild(spacerLabel);

			MenuLabel *styleLabel = new MenuLabel();
			styleLabel->text = "Style";
			menu->addChild(styleLabel);

			DejavuStyleItem *style1Item = new DejavuStyleItem();
			style1Item->text = "Orange";// 
			style1Item->module = module;
			style1Item->style= STYLE_ORANGE;
			menu->addChild(style1Item);

			DejavuStyleItem *style2Item = new DejavuStyleItem();
			style2Item->text = "Bright";// 
			style2Item->module = module;
			style2Item->style= STYLE_BRIGHT;
			menu->addChild(style2Item);
				
			DejavuStyleItem *style3Item = new DejavuStyleItem();
			style3Item->text = "Dark";// 
			style3Item->module = module;
			style3Item->style= STYLE_DARK;
			menu->addChild(style3Item);
		}
	}
};
Model *modelDejavu = createModel<Dejavu, DejavuWidget> ("Dejavu");