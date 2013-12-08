using UnityEngine;
using System.Collections;

public interface ITriggered {
	void OnTriggeredEnter ();
	void OnTriggeredStay ();
	void OnTriggeredExit ();
}