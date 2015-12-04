// ProgressThread.cpp : implementation file
//

#include "stdafx.h"
#include "progressbar1.h"
#include "ProgressThread.h"
#include "ProgressCtrlWithTimer.h"

#define WM_PLAY_PROGRESS_BAR WM_APP
#define WM_STOP_PROGRESS_BAR (WM_APP+1)

// CProgressThread

IMPLEMENT_DYNCREATE(CProgressThread, CWinThread)

CProgressThread::CProgressThread(const CProgressCtrl* reference_ctrl) : 
m_progress_ctrl(NULL), m_reference_ctrl(reference_ctrl), m_is_playing(false)
{
	m_bAutoDelete = FALSE; // This allows us to safely delete m_progress_ctrl
	                       // when calling EndThread.
}

CProgressThread::CProgressThread() : m_progress_ctrl(NULL), m_reference_ctrl(NULL)
{
}

CProgressThread::~CProgressThread()
{
	if (m_progress_ctrl)
		delete m_progress_ctrl;
}

BOOL CProgressThread::InitInstance()
{
	// This function is invoked in the new UI thread.
	// Creation of m_progress_ctrl is done in this thread, so that
	// the message pump of CWinThread will dispatch messages to it.
	m_progress_ctrl = new CProgressCtrlWithTimer;

	// The following calculation of r ensures that m_progress_ctrl has
	// the exact same position and dimensions of m_reference_ctrl.
	CRect r;
	m_reference_ctrl->GetWindowRect(r);
	CWnd* parent = m_reference_ctrl->GetParent();
	parent->ScreenToClient(r);

	// By calling m_reference_ctrl->GetStyle(), we ensure that 
	// m_progress_ctrl has the style of m_reference_ctrl.
	m_progress_ctrl->Create(m_reference_ctrl->GetStyle(),r,parent,1);

	return TRUE;
}

void CProgressThread::EndThread()
{
	// The casting operator from CWinThread to HANDLE returns a handle
	// to the thread.
	HANDLE h = *this;
	
	// Sending WM_QUIT causes GetMessage in CWinThread::MessagePump() to return FALSE.
	// This causes termination of the thread. The exit code of the thread
	// will be the parameter sent to the WM_QUIT message.
	WPARAM exit_code = 1;
	PostThreadMessage(WM_QUIT,exit_code,0);

	// We wait for the thread to end, and then we can safely delete m_progress_ctrl.
	WaitForSingleObject(h,INFINITE);
	delete this;
}

// Start to play the progress bar. 
// Whenever timer_milliseconds pass, we advance the position of the progress bar by pos_advance
void CProgressThread::Play(unsigned int timer_milliseconds, int pos_advance)
{
	if (m_is_playing)
		return;
	m_is_playing = true;
	PostThreadMessage(WM_PLAY_PROGRESS_BAR,timer_milliseconds,pos_advance);
}

// Stop playing the progress bar
void CProgressThread::Stop()
{
	if (!m_is_playing)
		return;
	m_is_playing = false;
	PostThreadMessage(WM_STOP_PROGRESS_BAR,0,0);
}

void CProgressThread::OnPlayProgressBar(WPARAM wParam, LPARAM lParam)
{
	m_progress_ctrl->Play((unsigned int)wParam,(int)lParam);
}

void CProgressThread::OnStopProgressBar(WPARAM wParam, LPARAM lParam)
{
	m_progress_ctrl->Stop();
}

BEGIN_MESSAGE_MAP(CProgressThread, CWinThread)
	ON_THREAD_MESSAGE(WM_PLAY_PROGRESS_BAR,OnPlayProgressBar)
	ON_THREAD_MESSAGE(WM_STOP_PROGRESS_BAR,OnStopProgressBar)
END_MESSAGE_MAP()
