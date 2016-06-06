#pragma	once

#include "Feat.h"
#include "Angles.h"
#include <string>

#pragma pack (push, progitr_align, 8)							// 8 byte alignment for following types

namespace GCApi
{

//--------------------------- AxisName -----------------------

struct AxisName
{
	AxisName()						{ s[0] = 0; }
	
	operator char * ()				{ return s; }
	operator const char * () const	{ return s; }
 
	char s[16];
};

//--------------------------- ProgItr -----------------------

class ProgItr
{
	private:
		void *pi_;
		bool done_;
		bool owned_;
		
	public:
		static const int cur_tool = 0;
		static const int no_tool = - 1;
		static const int cur_wp = 0;
		
		ProgItr()
			: owned_(true)
		{
			API_VERIFY(gc_GetProgIterator(&pi_));
			
			gc_ProgItrParams params;
			gc_InitProgItrParams(params);
			reset(params);
		}
		
		ProgItr(const ProgItr &src)
			: pi_(src.pi_), done_(src.done_), owned_(true)
		{
			if (pi_)
				API_VERIFY(gc_ProgIteratorCopy(pi_, &pi_));
		}
		
		explicit ProgItr(const gc_ProgItrParams &params)
			: owned_(true)
		{
			API_VERIFY(gc_GetProgIterator(&pi_));
			reset(params);
		}
		
		ProgItr(void *p, bool owned)
			: pi_(p), owned_(owned)
		{
			if (pi_)
				API_VERIFY(gc_ProgIteratorDone(pi_, done_));
			else
				done_ = true;
		}
		
		~ProgItr()
		{
			if (pi_ && owned_)
				API_VERIFY(gc_ProgIteratorDelete(pi_));
		}
		
		void swap(ProgItr &that)
		{
			std::swap(pi_, that.pi_);
			std::swap(done_, that.done_);
			std::swap(owned_, that.owned_);
		}
		
		ProgItr & operator = (const ProgItr &rhs)
		{
			ProgItr(rhs).swap(*this);
			return *this;
		}
		
		void * operator () ()
		{
			return pi_;
		}

		const void * operator () () const
		{
			return pi_;
		}
		
		void reset(const gc_ProgItrParams &params)
		{
			API_VERIFY(gc_ProgIteratorReset(pi_, const_cast<gc_ProgItrParams*>(&params)));
			done_ = (gc_ProgIteratorNext(pi_) < 0);
		}

		ProgItr & operator ++ ()
		{
			// pre-increment operator
			if (!done_)
				done_ = (gc_ProgIteratorNext(pi_) < 0);
			return *this;
		}
		
		bool done() const
		{
			return done_;
		}
		
		bool flow_done(int flow) const
		{
			int done = true;
			API_VERIFY(gc_GetProgItrFlowDone(pi_, flow, &done));
			return done != 0;
		}
		
		bool flow_blocked(int flow) const
		{
			int blocked = false;
			API_VERIFY(gc_GetProgItrFlowBlocked(pi_, flow, &blocked));
			return blocked != 0;
		}
		
		int syncs_released() const
		{
			int nsyncs = 0;
			API_VERIFY(gc_GetProgItrNumReleasedSyncs(pi_, &nsyncs));
			return nsyncs;
		}
		
		gc_SyncID released_sync_id(int ix) const
		{
			gc_SyncID sync_id;
			API_VERIFY(gc_GetProgItrReleasedSyncID(pi_, ix, &sync_id));
			return sync_id;
		}
		
		double elapsed_time() const
		{
			double time = 0.0;
			gc_ProgIteratorTime(pi_, &time);	// may return error if time not tracked in pi params
			return time;
		}
		
		teProgItrState get_state(int flow = 1) const
		{
			int state;
			API_VERIFY(gc_GetProgItrFeatState(pi_, flow, &state));
			return static_cast<teProgItrState>(state);
		}
		
		int get_op(int flow = 1) const
		{
			int op = 0;
			API_VERIFY(gc_GetProgItrOpNum(pi_, flow, &op));
			return op;
		}
		
		int get_op_instance(int flow = 1) const
		{
			int instance = 1;
			API_VERIFY(gc_GetProgItrOpInstance(pi_, flow, &instance));
			return instance;
		}
		
		int get_next_op(int flow = 1) const
		{
			int op = 0;
			API_VERIFY(gc_GetProgItrNextOpNum(pi_, flow, &op));
			return op;
		}
		
		int get_next_op_instance(int flow = 1) const
		{
			int instance = 1;
			API_VERIFY(gc_GetProgItrNextOpInstance(pi_, flow, &instance));
			return instance;
		}
		
		int get_tool(int flow = 1) const
		{
			int tool = 0;
			API_VERIFY(gc_GetProgItrToolNum(pi_, flow, &tool));
			return tool;
		}
		
		int get_next_tool(int flow = 1) const
		{
			int tool = 0;
			API_VERIFY(gc_GetProgItrNextToolNum(pi_, flow, &tool));
			return tool;
		}
		
		int get_tg(int flow = 1) const
		{
			int tg = 1;
			API_VERIFY(gc_GetProgItrTGNum(pi_, flow, &tg));
			return tg;
		}
		
		int get_next_tg(int flow = 1) const
		{
			int tg = 1;
			API_VERIFY(gc_GetProgItrNextTGNum(pi_, flow, &tg));
			return tg;
		}
		
		int get_wp(int flow = 1) const
		{
			int wp = 1;
			API_VERIFY(gc_GetProgItrWPNum(pi_, flow, &wp));
			return wp;
		}
		
		int get_next_wp(int flow = 1) const
		{
			int wp = 1;
			API_VERIFY(gc_GetProgItrNextWPNum(pi_, flow, &wp));
			return wp;
		}
		
		double get_feed_rate(int flow = 1) const
		{
			double feed = 0.0;
			API_VERIFY(gc_GetProgItrFeedRateEx(pi_, flow, &feed));
			return feed;
		}

		bool feed_per_rev(int flow = 1) const
		{
			bool val = false;
			API_VERIFY(gc_GetProgItrFeedPerRev(pi_, flow, val));
			return val;
		}
		
		Angles get_angles(int flow, double t) const
		{
			Angles abc;
			API_VERIFY(gc_GetProgItrRotAngles(pi_, flow, t, abc.coord));
			return abc;
		}

		Matrix &to_wkplane_mx(int flow, double t, Matrix &mx = Matrix()) const
		{
			API_VERIFY(gc_GetProgItrRotMatrix(pi_, flow, t, mx.el[0]));
			Classify(mx);
			return mx;
		}

		Matrix to_mach_mx(int flow, double t, Matrix &mx = Matrix()) const
		{
			API_VERIFY(gc_GetProgItrMachMatrix(pi_, flow, t, mx.el[0]));
			Classify(mx);
			return mx;
		}
		
		teGeoType get_feat_type(int flow = 1) const
		{
			int t = - 1;
			gc_GetProgItrFeatType(pi_, flow, &t);
			return static_cast<teGeoType>(t);
		}

		Feat get_feat(int flow = 1) const
		{
			void *feat_ptr = nullptr;
			API_VERIFY(gc_GetProgItrFeat(pi_, flow, &feat_ptr));
			return Feat(feat_ptr);
		}
		
		void get_feat(Feat &feat, int flow = 1) const
		{
			void *feat_ptr;
			API_VERIFY(gc_GetProgItrFeat(pi_, flow, &feat_ptr));
			Feat(feat_ptr).swap(feat);
		}
		
		double get_start_param(int flow = 1) const
		{
			double t;
			API_VERIFY(gc_GetProgItrFeatParams(pi_, flow, &t, NULL));
			return t;
		}
		
		double get_end_param(int flow = 1) const
		{
			double t;
			API_VERIFY(gc_GetProgItrFeatParams(pi_, flow, NULL, &t));
			return t;
		}
		
		int tool_cs(int flow = 1) const
		{
			int cs = 0;
			API_VERIFY(gc_GetProgItrToolCS(pi_, flow, &cs));
			return cs;
		}

		int feat_cs(int flow = 1) const
		{
			int cs = 0;
			API_VERIFY(gc_GetProgItrFeatCS(pi_, flow, &cs));
			return cs;
		}

		bool crc_on(int flow = 1) const
		{
			int on;
			API_VERIFY(gc_GetProgItrCRCState(pi_, flow, &on));
			return on != false;
		}
		
		int inter_op_evt_count(int flow) const
		{
			int n = 0;
			API_VERIFY(gc_GetProgItrInterOpEventCount(pi_, flow, &n));
			return n;
		}
		
		gc_InterOpEvent inter_op_evt(int flow, int ix) const
		{
			gc_InterOpEvent evt = gc_eNumInterOpEvents;
			API_VERIFY(gc_GetProgItrInterOpEvent(pi_, flow, ix, &evt));
			return evt;
		}
		
		void clear_inter_op_evts(int flow)
		{
			API_VERIFY(gc_ClearProgItrInterOpEvents(pi_, flow));
		}

		std::string &get_axis_set(int flow, std::string &axis_set = std::string()) const
		{
			char s[256];
			API_VERIFY(gc_GetProgItrAxisSet(pi_, flow, s));
			axis_set = s;
			return axis_set;
		}
		
		std::string &get_next_axis_set(int flow, std::string &axis_set = std::string()) const
		{
			char s[256];
			API_VERIFY(gc_GetProgItrNextAxisSet(pi_, flow, s));
			axis_set = s;
			return axis_set;
		}
		
		gc_InterpSet &get_interp_set(int flow, gc_InterpSet &interp_set = gc_InterpSet()) const
		{
			API_VERIFY(gc_GetProgItrInterpSet(pi_, flow, interp_set));
			return interp_set;
		}
		
		gc_InterpSet &get_next_interp_set(int flow, gc_InterpSet &interp_set = gc_InterpSet()) const
		{
			API_VERIFY(gc_GetProgItrNextInterpSet(pi_, flow, interp_set));
			return interp_set;
		}
		
		int tool_loaded(int tg = 1) const
		{
			int tool;
			API_VERIFY(gc_GetProgItrTGToolNum(pi_, tg, &tool));
			return tool;
		}

		int tg_cur_wp(int tg = 1) const
		{
			int wp;
			API_VERIFY(gc_GetProgItrTGCurWP(pi_, tg, &wp));
			return wp;
		}

		Pt3d tg_pos(int tg = 1, int tool = no_tool, int wp = cur_wp) const
		{
			Pt3d p;
			API_VERIFY(gc_GetProgItrTGPos(pi_, tg, tool, wp, p.coord));
			return p;
		}

		Angles tg_angles(int tg = 1) const
		{
			Angles abc;
			API_VERIFY(gc_GetProgItrTGAngles(pi_, tg, abc.coord));
			return abc;
		}
		
		void set_tg_angles(const Angles &abc, int tg = 1)
		{
			for (int i=a_axis; i<=c_axis; ++i)
				gc_SetProgItrTGAngle(pi_, tg, i, abc[i]);
		}

		bool tg_spindle_on(int tg = 1) const
		{
			return tg_rpm(tg) > 0.0;
		}

		bool tg_spindle_ccw(int tg = 1) const
		{
			int ccw;
			API_VERIFY(gc_GetProgItrTGDir(pi_, tg, &ccw));
			return ccw != 0;
		}

		double tg_rpm(int tg = 1) const
		{
			double rpm;
			API_VERIFY(gc_GetProgItrTGRPM(pi_, tg, &rpm));
			return rpm;
		}

		bool tg_tcp_on(int tg = 1) const
		{
			int on;
			API_VERIFY(gc_GetProgItrTGTCPState(pi_, tg, &on));
			return on != 0;
		}

		bool wp_spindle_on(int wp = 1) const
		{
			return wp_rpm(wp) > 0.0;
		}

		bool wp_spindle_ccw(int wp = 1) const
		{
			int ccw;
			API_VERIFY(gc_GetProgItrWPDir(pi_, wp, &ccw));
			return ccw != 0;
		}

		double wp_rpm(int wp = 1) const
		{
			double rpm;
			API_VERIFY(gc_GetProgItrWPRPM(pi_, wp, &rpm));
			return rpm;
		}

		bool wp_rpm_const(int wp = 1) const
		{
			int fixed;
			API_VERIFY(gc_GetProgItrWPRPMFixed(pi_, wp, &fixed));
			return fixed != 0;
		}

		Pt3d wp_pos(int wp = 1) const
		{
			Pt3d p;
			API_VERIFY(gc_GetProgItrWPPos(pi_, wp, p.coord));
			return p;
		}

		int axis_count() const
		{
			int n = 0;
			API_VERIFY(gc_GetProgItrAxisCount(pi_, &n));
			return n;
		}
		
		void get_axis_info(AxisName names[], double vals[]) const
		{
			API_VERIFY(gc_GetProgItrAxes(pi_, names ? &names[0].s : NULL, vals, NULL, NULL, NULL));
		}

		int errors() const
		{
			int n = 0;
			API_VERIFY(gc_GetProgItrErrorCount(pi_, &n));
			return n;
		}
		
		gc_ProgItrErr error_type(int ix) const
		{
			gc_ProgItrErr type;
			API_VERIFY(gc_GetProgItrErrorType(pi_, ix, &type));
			return type;
		}

		void clear_errors() const
		{
			API_VERIFY(gc_ClearProgItrErrors(pi_));
		}
		
		teProgItrRotErr rot_error(int flow = 1, double param = 1.0) const
		{
			teProgItrRotErr err = eProgRotNoErr;
			API_VERIFY(gc_GetProgItrRotError(pi_, flow, param, &err));
			return err;
		}
};

}	// end namespace GCApi

#pragma pack (pop, progitr_align)						// restore struct alignment
