using UnityEngine;
using System.Collections;

public class Laser : MonoBehaviour {

	 void OnCollisionEnter(Collision other) {
		Debug.Log(other.gameObject.name);
	}
}
